#pragma once

// #define FLY_PLATFORM_LINUX
// #ifdef FLY_PLATFORM_LINUX

extern flyCore::Application* flyCore::CreateApplication();

int main(int argc, char** argv)
{
    flyCore::Log::Init();
    flyCore::Log::GetCoreLogger()->warn("Initialized Log!");
    flyCore::Log::GetClientLogger()->warn("Initialized Log!");

    auto app = flyCore::CreateApplication();
    app->Run();
    delete app;
}

// #endif
