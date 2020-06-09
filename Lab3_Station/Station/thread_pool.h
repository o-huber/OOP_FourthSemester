#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
    std::vector<std::thread> thread_pool;
    std::queue<std::function<void()>> tasks;

    std::mutex tasks_mutex;
    std::condition_variable condition;

    std::atomic_bool stopped = false;   // success stopped pool
    std::atomic_bool terminate = false; // trying to stop pool
public:
    ThreadPool(size_t threads) {
        for (size_t i = 0; i < threads; ++i)
            thread_pool.emplace_back(&ThreadPool::runner, this);
    }

    ~ThreadPool() {
        if (!stopped)
            shut_down();
    }

    void add_task(std::function<void()> f) {
        {
            // scope for locking queue
            std::unique_lock<std::mutex> lock(tasks_mutex);
            tasks.push(std::move(f));
        }
        condition.notify_one(); // Wake up one (random) thread for task
    }

    void shut_down() {
        terminate = true;
        condition.notify_all();

        for (auto &th : thread_pool)
            th.join();

        thread_pool.clear();
        stopped = true;
    }

private:
    void runner() {
        std::function<void()> task;
        while (true) {
            {
                std::unique_lock<std::mutex> lock(tasks_mutex);

                // continue when: any task in tasks or terminate
                condition.wait(lock, [this] {
                    return !tasks.empty() || terminate;
                });

                // if terminate and tasks is empty go out form runner
                if (terminate && tasks.empty())
                    return;

                task = std::move(tasks.front());
                tasks.pop();
            }
            task();
        }
    }
};
