#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>


class Timer {
    typedef std::chrono::high_resolution_clock high_resolution_clock;
    typedef std::chrono::milliseconds milliseconds;

    high_resolution_clock::time_point d_start;

public:
    explicit Timer(bool run = false)
    {
        if (run)
            reset();
    }

    void reset()
    {
        d_start = high_resolution_clock::now();
    }

    milliseconds elapsed() const
    {
        return std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - d_start);
    }

    friend std::ostream &operator<<(std::ostream &out, Timer const &timer)
    {
        return out << timer.elapsed().count();
    }
};

#endif
