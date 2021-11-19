#pragma once

#include <string>
#include <memory>

#include "fenix/core/window.hh"
#include "fenix/core/layer_stack.hh"
#include "fenix/core/timestep.hh"
#include "fenix/events/application_event.hh"

#include "fenix/gui/imgui_layer.hh"

namespace fenix {

    class Application
    {
    public:
        Application(const std::string& name = "Fenix App");
        virtual ~Application();

        void Run();

        void OnEvent(Event& evt);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        void Close();

        ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

        Window& GetWindow() { return *m_Window; }

        static Application& GetApp() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent&);
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

} // namespace fenix
