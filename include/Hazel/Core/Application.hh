#pragma once

#include <string>
#include <memory>

#include "Hazel/Core/Window.hh"
#include "Hazel/Core/LayerStack.hh"
#include "Hazel/Core/Events/Event.hh"
#include "Hazel/Core/Events/ApplicationEvent.hh"

#include "Hazel/ImGui/ImGuiLayer.hh"

// TEMP: Temporary
#include "Platform/OpenGL/OpenGLShader.hh"
#include "Hazel/Renderer/Buffer.hh"
#include "Hazel/Renderer/VertexArray.hh"

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

        // TEMP: Temporary
        std::shared_ptr<OpenGLShader> m_Shader;
        std::shared_ptr<VertexArray> m_TriangleVA;

        std::shared_ptr<OpenGLShader> m_BlueShader;
        std::shared_ptr<VertexArray> m_SquareVA;

        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

} // namespace Hazel
