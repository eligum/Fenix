#pragma once

#include <chrono>

namespace fenix {

    class Timestep
    {
    public:
        using Seconds = std::chrono::duration<float>;
        using MilliSeconds = std::chrono::duration<float, std::ratio<1, 1000>>;

        Timestep(Seconds time = {})
            : m_Time(time)
        {}

        operator float() const { return m_Time.count(); }

        Seconds GetSeconds() const { return m_Time; }
        MilliSeconds GetMiliseconds() const { return m_Time; }
    private:
        Seconds m_Time;
    };

}
