#include "Application.hh"
#include "Log.hh"
#include "Events/ApplicationEvent.hh"

namespace flyCore {

    Application::Application()
    {
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

        while (true)
            ;
    }

} // namespace flyCore
