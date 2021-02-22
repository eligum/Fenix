#pragma once

#include <string>

namespace flyCore {

    class Application
    {
    public:
        // Application(const std::string& title = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);
        Application() = default;
        virtual ~Application() = default;

        void Run();
    };

    // To be defined in CLIENT
    Application* CreateApplication();

}
