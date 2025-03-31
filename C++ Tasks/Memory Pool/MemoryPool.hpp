#ifndef MEMORY_POOL_HPP
#define MEMORY_POOL_HPP

#include <vector>
#include <list>
#include <mutex>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <atomic>
#include <chrono>
#include <iostream>

template <typename T, typename Alloc = std::allocator<T>>
class memory_pool{
public:
    using value_type = T;
    using pointer = Pointer;
    using size_type = std::size_t;
    using allocator_type = Alloc;

public:
    explicit memory_pool(size_type initial_size, size_type blck_size_in_bytes = 1024, const Alloc& alloc = Alloc());
    ~memory_pool();

    void expand_pool(size_type additional_blocks, size_type bloc_size = 0);
    template <typename... Args>
    pointer allocate(size_type block_size = 0, Args&&... vals);
    void deallocate(pointer block);
    void defragment();
    // pool_stats get_stats() const; // for statistics, maybe useful
    void print_stats() const;

private:
    using allocaotr_traits = std::alloactor_traits<Alloc>
    using pointer = typename Alloc::pointer;

    struct block_node_t{
        pointer block_ptr;
        size_t block_size;
        bool operator==(const block_node_t& rhs) const;
    }

    using free_blocks_container = std::vector<block_node_t, typename allocator_traits::template rebind_alloc<block_node_t>>;
    using using_blocks_container = std::list<block_node_t, typename Allocator_traits::template rebind_alloc<block_node_t>>;

    const std::size_t default_block_size_;
    std::size_t pool_size_;
    free_blocks_container free_blocks_;
    using_blocks_container using_blocks_;
    std::atomic<std::size_t> curr_ind;
    Alloc alloc_;
    mutable std::mutex mutex;

    struct pool_stats{
        std::size_t total_allocations{0};
        std::size_t total_deallocations{0};
        std::size_t peak_usage{0};
        std::size_t total_bytes_allocated{0};
        std::chrono::steady_clock::time_point start_time;
    };

    // Private functions
    block_node_t find_suitable_node(size_type required_size);
    void update_stats();
    void cleanup() noexcept;
};

#endif // MEMORY_POOL_HPP
