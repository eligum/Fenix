#include "Fenix/Core/Application.hh"
#include "Fenix/Core/Log.hh"
#include "Fenix/Events/ApplicationEvent.hh"

#include "Fenix/Renderer/Renderer.hh"

#include <GLFW/glfw3.h>

namespace fenix {

    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& name)
    {
        FX_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create({ name, 1280, 720 }));
        m_Window->SetEventCallback(FX_BIND_EVENT_FN(Application::OnEvent));
        m_Window->SetVSync(true);

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& evt)
    {
        EventDispatcher dispatcher(evt);
        dispatcher.Dispatch<WindowCloseEvent>(FX_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(FX_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (evt.Handled)
                break;
            (*it)->OnEvent(evt);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }

    void Application::Run()
    {
        while (m_Running)
        {
            // TEMP: This shouldn't depend on glfw.
            float time = static_cast<float>(glfwGetTime());
            Timestep timestep = Timestep::Seconds(time - m_LastFrameTime);
            m_LastFrameTime = time;

            // In Windows minimizing causes the screen to get resized to 0,0 while still consuming resources,
            // to avoid wasting CPU or GPU time we only render when the window size is greater than zero.
            if (!m_Minimized)
            {
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(timestep);
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::Close()
    {
        m_Running = false;
    }

    bool Application::OnWindowClose(WindowCloseEvent&)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& evt)
    {
        if (evt.GetWidth() == 0 || evt.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;
        Renderer::OnWindowResize(evt.GetWidth(), evt.GetHeight());

        return false;
    }

} // namespace fenix
