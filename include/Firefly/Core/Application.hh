#pragma once

#include "Firefly/flypch.hh"

namespace flyCore {

    class Application
    {
    public:
        // Application(const std::string& title = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);
        Application();
        virtual ~Application();

        void Run();
    };

    // To be defined in CLIENT
    Application* CreateApplication();

}
