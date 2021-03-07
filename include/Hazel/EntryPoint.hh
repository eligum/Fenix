#pragma once

// #define HZ_PLATFORM_LINUX
// #ifdef HZ_PLATFORM_LINUX

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
    Hazel::Log::Init();
    HZ_CORE_INFO("Initialized Log!");

    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}

// #endif
