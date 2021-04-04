#pragma once

extern Fenix::Application* Fenix::CreateApplication();

int main(int, char**)
{
    Fenix::Log::Init();
    FX_CORE_WARN("Initialized Log!");

    auto app = Fenix::CreateApplication();
    app->Run();
    delete app;

    return 0;
}
