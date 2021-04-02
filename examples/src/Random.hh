#pragma once

#include <random>

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

} // namespace Fenix
