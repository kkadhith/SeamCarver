#pragma once

#include <chrono>
#include <iostream>

/// @brief Custom timer to benchmark performance in seconds
///
/// main functions: start() and stop()
struct timer {
    private:
        using time_t = decltype(std::chrono::system_clock::now());
        time_t last;
        bool on;

        auto get_time() {
            return std::chrono::system_clock::now();
        }

        double diff(time_t t1, time_t t2) {
            return std::chrono::duration_cast<std::chrono::microseconds>(t1-t2).count() / 1000000.0;
        }

    public:
        timer() : on(false) {
            start();
        }

        void start() {
            on = true;
            last = get_time();
        }

        double stop() {
            on = false;
            return diff(get_time(), last);
        }
};