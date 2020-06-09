#pragma once
#include <mutex>
#include <shared_mutex>

template <class T, class Mutex = std::mutex>
class Synchronized {
    T value;
    T &ref_;
    mutable Mutex m;
public:
    explicit Synchronized(T init = T{})
        : value(std::move(init)), ref_(value) {}

    class Access {
        T &ref_;
        std::lock_guard<Mutex> lock;
    public:
        Access(T &ref, Mutex &m)
            : ref_(ref), lock({m}) {}
        auto &ref() {
            return ref_;
        }
        const auto &ref() const {
            return ref_;
        }
    };

    auto get() {
        return Access{ref_, m};
    }
    const auto get() const {
        return Access{ref_, m};
    }
};
