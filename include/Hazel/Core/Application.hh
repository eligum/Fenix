#pragma once

#include <string>
#include <memory>

#include "Hazel/Core/Window.hh"
#include "Hazel/Core/LayerStack.hh"
#include "Hazel/Core/Events/Event.hh"
#include "Hazel/Core/Events/ApplicationEvent.hh"

#include "Hazel/ImGui/ImGuiLayer.hh"

#include "Platform/OpenGL/OpenGLShader.hh"

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
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        // Temporary
        uint32_t m_Vao, m_Vbo, m_IndexBuffer;
        std::unique_ptr<OpenGLShader> m_Shader;

        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

} // namespace Hazel
