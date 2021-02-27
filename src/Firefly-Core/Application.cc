#include "Application.hh"
#include "Log.hh"
#include "Events/ApplicationEvent.hh"

namespace flyCore {

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

} // namespace flyCore
