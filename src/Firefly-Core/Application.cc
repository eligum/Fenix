#include "Application.hh"
#include "Log.hh"
#include "Events/ApplicationEvent.hh"

namespace flyCore {

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& e)
    {
        FLY_CORE_INFO("{0}", e);
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

} // namespace flyCore
