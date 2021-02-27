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
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication))
        {
            FLY_INFO(e);
            FLY_ERROR(e);
        }

        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

} // namespace flyCore
