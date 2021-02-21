#pragma once

// #define FLY_PLATFORM_LINUX
// #ifdef FLY_PLATFORM_LINUX

extern flyCore::Application* flyCore::CreateApplication();

int main(int argc, char** argv)
{
    auto app = flyCore::CreateApplication();
    app->Run();
    delete app;
}

// #endif
