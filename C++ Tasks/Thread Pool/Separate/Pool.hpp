#ifndef POOL_HPP
#define POOL_HPP

#include <mutex>
#include <thread>
#include <queue>
#include <functional>
#include <future>
#include <condition_variable>
#include <vector>
#include <stdexcept>
#include <utility>
#include <atomic>

enum class TaskPriority : uint8_t {
    LOW,
    NORMAL,
    HIGH
};

class thread_pool{
public:
    explicit thread_pool(std::size_t threads);
    ~thread_pool();

    template <typename Func, typename... Args>
    auto enqueue(Func&& func, Args&&... args, TaskPriority priority = TaskPriority::NORMAL) 
                 -> std::future<std::invoke_result_t<std::decay_t<Func>, std::decay_t<Args>...>>;

    std::size_t thread_count() const;
    std::size_t system_hardware_concurrency() const;
    std::size_t pending_tasks() const;
    void resize(std::size_t new_size);
    void pause();
    void resume();

private:
    struct task_ {
        std::function<void()> func;
        TaskPriority priority;
        
        bool operator<(const task_& other) const {
            return priority < other.priority;
        }
    };

    static constexpr std::size_t MAX_THREADS = 1000;
    std::vector<std::jthread> workers_;
    std::priority_queue<task_> tasks_;
    const std::size_t cores_number_;
    std::atomic<bool> stop_{false};
    std::atomic<bool> paused_{false};
    std::atomic<std::size_t> active_threads_{0};

    mutable std::mutex q_mtx_; // queue mutex
    std::condition_variable condition_;
};

template <typename Func, typename... Args>
inline auto thread_pool::enqueue(Func &&func, Args &&...args, TaskPriority priority) -> std::future<std::invoke_result_t<std::decay_t<Func>, std::decay_t<Args>...>>
{
    using return_type = std::invoke_result_t<std::decay_t<Func>, std::decay_t<Args>...>;

    auto task = std::make_shared<std::packaged_task<return_type()>> (
        std::bind(std::function<Func>(f), std::function<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(q_mtx_);
        if (stop_) {
            throw std::runtime_error("enqueue on stopped thread_pool");
        }

        tasks_.push(task_{[task]() {(*task)(); }, priority});
    }

    condition_.notify_one();
    return res;
}


#endif // POOL_HPP

