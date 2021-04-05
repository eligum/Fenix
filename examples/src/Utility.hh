#pragma once

#include <random>
#include <chrono>
#include <iostream>

namespace Fenix {

    class Random
    {
    public:
        static void Init() { s_RandomEngine.seed(std::random_device()()); }
        static int32_t GenerateInt() { return s_Distribution(s_RandomEngine); }
    private:
        static std::mt19937 s_RandomEngine;
        static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
    };


    /// @class LTimer
    ///
    /// Timer implemented with RAII in mind.
    class LTimer
    {
    public:
        LTimer(const char* name)
            : m_Name(name), m_Stopped(false)
        {
            m_TpStart = std::chrono::steady_clock::now();
        }

        ~LTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            m_TpEnd = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration<float, std::milli>(m_TpEnd - m_TpStart);
            m_Stopped = true;

            std::cout << m_Name << ": " << duration.count() << "ms" << '\n';
        }
    private:
        const char* m_Name;
        bool m_Stopped;
        std::chrono::time_point<std::chrono::steady_clock> m_TpStart, m_TpEnd;
    };

} // namespace Fenix
