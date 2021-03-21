#pragma once

// #define FX_PLATFORM_LINUX
// #ifdef FX_PLATFORM_LINUX

extern Fenix::Application* Fenix::CreateApplication();

int main(int argc, char** argv)
{
    Fenix::Log::Init();
    FX_CORE_WARN("Initialized Log!");

    auto app = Fenix::CreateApplication();
    app->Run();
    delete app;
}

// #endif
