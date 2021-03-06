#pragma once

#include <string>
#include <memory>

#include "Window.hh"
#include "LayerStack.hh"
#include "Events/Event.hh"
#include "Events/ApplicationEvent.hh"

namespace Hazel {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& evt);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        static Application& GetApp() { return *s_Instance; }
        Window& GetWindow() { return *m_Window; }
    private:
        bool OnWindowClose(WindowCloseEvent& evt);
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

} // namespace Hazel
