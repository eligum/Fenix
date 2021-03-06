#pragma once

// #define FLY_PLATFORM_LINUX
// #ifdef FLY_PLATFORM_LINUX

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
    Hazel::Log::Init();
    FLY_CORE_INFO("Initialized Log!");

    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}

// #endif
