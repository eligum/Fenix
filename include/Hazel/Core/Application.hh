#pragma once

#include <string>
#include <memory>

#include "Hazel/Core/Window.hh"
#include "Hazel/Core/LayerStack.hh"
#include "Hazel/Core/Timestep.hh"
#include "Hazel/Events/ApplicationEvent.hh"

#include "Hazel/ImGui/ImGuiLayer.hh"

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

        Window& GetWindow() { return *m_Window; }

        static Application& GetApp() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& evt);
        bool OnWindowResize(WindowResizeEvent& evt);
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false; // Only needed for Windows OS
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;

        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

} // namespace Hazel
