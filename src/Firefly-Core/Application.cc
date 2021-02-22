#include "Firefly/Core/Application.hh"
#include "Firefly/Core/Log.hh"
#include "Firefly/Core/Events/ApplicationEvent.hh"

namespace flyCore {

    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication))
            FLY_INFO(e);

        while (true)
            ;
    }

} // namespace flyCore
