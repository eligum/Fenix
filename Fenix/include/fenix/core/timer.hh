#pragma once

#include <chrono>

namespace fenix {

    class Timer
    {
    public:
        using Seconds = std::chrono::duration<double>;
        using Millis  = std::chrono::duration<double, std::milli>;
        using Nanos   = std::chrono::duration<double, std::nano>;
        using Frames  = std::chrono::duration<double, std::ratio<1, 60>>;

    public:
        Timer()
        {
            Reset();
        }

        void Reset()
        {
            m_Start = std::chrono::steady_clock::now();
        }

        /// @return The elapsed time in seconds since the las call to Timer::Reset().
        auto Elapsed()
        {
            return Seconds { std::chrono::steady_clock::now() - m_Start };
        }

    private:
        std::chrono::steady_clock::time_point m_Start;
    };

} // namespace fenix
