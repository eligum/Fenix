#pragma once

#include <string>

#include "Window.hh"

namespace flyCore {

    class Application
    {
    public:
        // Application(const std::string& title = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

}
