#pragma once

#include "fenix/core/base.hh"
#include "fenix/core/application.hh"

extern fenix::Application* fenix::CreateApplication();

int main(int /* argc */, char** /* argv */)
{
    fenix::Log::Init();
    FENIX_CORE_WARN("Initialized Log.");
    FENIX_CORE_WARN("All output is being written to a file.");

    auto app = fenix::CreateApplication();
    app->Run();
    delete app;
}
