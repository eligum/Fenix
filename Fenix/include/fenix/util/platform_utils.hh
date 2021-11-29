#pragma once

#include <string>

namespace fenix {

    class FileDialog
    {
    public:
        // These return empty string if cancelled
        static std::string OpenFile(const char* filter);
        static std::string SaveFile(const char* filter);
    };

} // namespace fenix
