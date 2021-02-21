#include "Application.hh"

#include <iostream>
#include <unistd.h>

namespace flyCore {

    void Application::Run()
    {
        while (true)
        {
            std::cout << "Welcome to firefly" << '\n';
            sleep(2);
        }
    }

} // namespace flyCore
