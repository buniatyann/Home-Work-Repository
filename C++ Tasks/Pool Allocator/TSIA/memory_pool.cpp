#include "memory_pool.hpp"

template <typename T, typename Alloc>
memory_pool<T, Alloc>::memory_pool(size_type initial_size, size_type block_size_in_bytes, const Alloc& alloc)
    : default_block_size_(block_size_in_bytes),
    pool_size_(initial_size),
    curr_ind(0),
    alloc_(alloc),
    free_blocks_(alloc),
    using_blocks_(alloc),
    stats{.start_time = std::chrono::steady_clock::now()} {
    expand_pool(initial_size, default_block_size_);
}

template <typename T, typename Alloc>
memory_pool<T, Alloc>::~memory_pool() {
    std::lock_guard<std::mutex> lock(mutex);
    cleanup();
}

template <typename T, typename Alloc>
void memory_pool<T, Alloc>::expand_pool(size_type additional_blocks, size_type block_size) {
    std::lock_guard<std::mutex> lock(mutex); // Locking to prevent concurrent access to pool
    block_size = block_size ? block_size : default_block_size_;

    try {
        for (size_type i = 0; i < additional_blocks; ++i) {
            pointer block = allocator_traits::allocate(alloc_, (block_size + sizeof(T) - 1) / sizeof(T));
            free_blocks_.push_back({block, block_size});
            stats.total_bytes_allocated += block_size;
        }
        pool_size_ += additional_blocks;
    } catch (...) {
        cleanup();
        throw;
    }
}

template <typename T, typename Alloc>
template <typename... Args>
typename memory_pool<T, Alloc>::pointer memory_pool<T, Alloc>::allocate(size_type block_size, Args&&... args) {
    std::lock_guard<std::mutex> lock(mutex); // Locking to protect memory allocation process

    block_size = block_size ? block_size : default_block_size_;
    block_node_t block_node = find_suitable_node(block_size);

    if (block_node.block_ptr == nullptr) {
        expand_pool(1, block_size);
        block_node = free_blocks_.back();
        free_blocks_.pop_back();
    } else {
        free_blocks_.erase(std::remove(free_blocks_.begin(), free_blocks_.end(), block_node), free_blocks_.end());
    }

    try {
        allocator_traits::construct(alloc_, block_node.block_ptr, std::forward<Args>(args)...);
        using_blocks_.push_back(block_node);
        update_stats();

        return block_node.block_ptr;
    } catch (...) {
        free_blocks_.push_back(block_node);
        throw;
    }
}

template <typename T, typename Alloc>
void memory_pool<T, Alloc>::deallocate(pointer block) {
    std::lock_guard<std::mutex> lock(mutex); // Locking to protect deallocation process

    auto it = std::find_if(using_blocks_.begin(), using_blocks_.end(), [block](const block_node_t& node) {
        return node.block_ptr == block;
    });

    if (it == using_blocks_.end()) {
        throw std::invalid_argument("Invalid block pointer");
    }

    allocator_traits::destroy(alloc_, block);
    block_node_t block_node = *it;
    using_blocks_.erase(it);
    free_blocks_.push_back(block_node);
    stats.total_deallocations++;
}

template <typename T, typename Alloc>
void memory_pool<T, Alloc>::defragment() {
    std::lock_guard<std::mutex> lock(mutex); // Locking to ensure thread-safety during defragmentation
    free_blocks_.shrink_to_fit();
    std::sort(free_blocks_.begin(), free_blocks_.end(), [](const block_node_t& a, const block_node_t& b) {
        return a.block_ptr < b.block_ptr;
    });
}

template <typename T, typename Alloc>
void memory_pool<T, Alloc>::print_stats() const {
    std::lock_guard<std::mutex> lock(mutex); // Locking to ensure stats are printed safely
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::steady_clock::now() - stats.start_time).count();

    std::cout << "Memory Pool Statistics:\n"
              << "Total capacity: " << pool_size_ << " blocks\n"
              << "Free blocks: " << free_blocks_.size() << "\n"
              << "Used blocks: " << using_blocks_.size() << "\n"
              << "Total allocations: " << stats.total_allocations << "\n"
              << "Total deallocations: " << stats.total_deallocations << "\n"
              << "Peak usage: " << stats.peak_usage << " blocks\n"
              << "Total bytes allocated: " << stats.total_bytes_allocated << "\n"
              << "Uptime: " << duration << " seconds\n";
}

template <typename T, typename Alloc>
bool memory_pool<T, Alloc>::block_node_t::operator==(const block_node_t& rhs) const {
    return this->block_ptr == rhs.block_ptr && this->block_size == rhs.block_size;
}

template <typename T, typename Alloc>
typename memory_pool<T, Alloc>::block_node_t memory_pool<T, Alloc>::find_suitable_node(size_type required_size) {
    for (const auto& block_node : free_blocks_) {
        if (block_node.block_size >= required_size) {
            return block_node;
        }
    }
    return {nullptr, 0};
}

template <typename T, typename Alloc>
void memory_pool<T, Alloc>::update_stats() {
    ++stats.total_allocations;
    stats.peak_usage = std::max(stats.peak_usage, using_blocks_.size());
}

template <typename T, typename Alloc>
void memory_pool<T, Alloc>::cleanup() noexcept {
    for (const auto& block_node : free_blocks_) {
        allocator_traits::deallocate(alloc_, block_node.block_ptr, (block_node.block_size + sizeof(T) - 1) / sizeof(T));
    }

    for (const auto& node : using_blocks_) {
        allocator_traits::destroy(alloc_, node.block_ptr);
        allocator_traits::deallocate(alloc_, node.block_ptr, (node.block_size + sizeof(T) - 1) / sizeof(T));
    }
}
