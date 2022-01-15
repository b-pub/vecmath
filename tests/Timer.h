/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/**
 * A Timer class for measuring durations.
 */
#ifndef TIMER_H
#define TIMER_H

#include <chrono>

/**
 * A Timer class for measuring durations.
 *
 * Usage:
 * - create it: Timer timer;
 * - start it:  timer.start();
 * - stop it:   timer.stop();
 * - get elapsed time: timer.elapsed();
 *
 * The same timer can be stopped/started multiple times:
 *
 * Calling start() is equivalent to a reset.
 *
 * Calls to stop() record the time passed since the last
 * call to start(). Thus, code can call stop() multiple
 * times to note elapsed time from a single start point
 * (to record multiple delta-points).
 */
class Timer {
  private:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

    TimePoint m_start;
    TimePoint m_end;

  public:
    Timer()
        : m_start()
        , m_end()
    { }

    void start()
    {
        m_end = m_start = Clock::now();
    }

    void end()
    {
        m_end = Clock::now();
    }

    /* Returns milliseconds */
    float elapsed()
    {
        return 1.0e3f * (m_end - m_start).count() / Clock::period::den;
    }
};

#endif // TIMER_H
