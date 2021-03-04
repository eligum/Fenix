#pragma once

#include <string>
#include <memory>

#include "Window.hh"
#include "LayerStack.hh"
#include "Events/Event.hh"
#include "Events/ApplicationEvent.hh"

namespace flyCore {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& evt);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        bool OnWindowClose(WindowCloseEvent& evt);
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

}
