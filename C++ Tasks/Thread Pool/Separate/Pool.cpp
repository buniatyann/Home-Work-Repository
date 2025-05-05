#include "Pool.hpp"
#include <iostream>

thread_pool::thread_pool(std::size_t threads) : cores_number_(std::min(threads, MAX_THREADS)) {
    if (threads > system_hardware_concurrency()) {
        std::cerr << "Warning: Thread count (" << threads 
                  << ") exeeds hardware concurrency (" << system_hardware_concurrency() 
                  << "). This may impact performance" << std::endl;
    }

    if (threads > MAX_THREADS) {
        std::cerr << "Warning. Thread count capped at " << MAX_THREADS << "." << std::endl;
    }

    resize(cores_number_);
}

thread_pool::~thread_pool() {
    stop_ = true;
    condition_.notify_all();
    // std::jthread automatically joins
}

std::size_t thread_pool::thread_count() const {
    return cores_number_;
}

std::size_t thread_pool::system_hardware_concurrency() const {
    return std::thread::hardware_concurrency();
}

std::size_t thread_pool::pending_tasks() const {
    std::unique_lock<std::mutex> lock(q_mtx_);
    return tasks_.size();
}

void thread_pool::resize(std::size_t new_size) {
    new_size = std::min(new_size, MAX_THREADS);
    if(new_size > system_hardware_concurrency()){
        std::cerr << "Warning: Resizing to " << new_size 
                  << " threads exceeds hardware concurrency (" << system_hardware_concurrency() 
                  << ")." << std::endl;
    }

    std::unique_lock<std::mutex> lock(q_mtx_);
    while (workers_.size() < new_size) { // Increase thread count
        workers_.emplace_back(
            [this] {
                ++active_threads_;
                while (!stop_) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->q_mtx_);
                        this->condition_.wait(lock, [this] {
                            return stop_ || (!paused_ && !tasks_.empty());
                        });

                        if (stop_ || (paused_ || tasks_.empty())) {
                            break;
                        }

                        task = std::move(tasks_.top().func);
                        tasks_.pop();

                        try {
                            task();
                        } catch (const std::exception& e) {
                            std::cerr << "Task exception " << e.what() << std::endl;
                        }
                    }
                }

                --active_threads_;
            }
        );
    }

    if (workers_.size() > new_size) { // Decrease thread count
        condition_.notify_all();
        while (workers_.size() > new_size && active_threads_ > new_size) {
            workers_.pop_back();
        }
    }
}

void thread_pool::pause() {
    std::unique_lock<std::mutex> lock(q_mtx_);
    paused_ = true;
}

void thread_pool::resume() {
    std::unique_lock<std::mutex> lock(q_mtx_);
    paused_ = false;
    condition_.notify_all();
}
