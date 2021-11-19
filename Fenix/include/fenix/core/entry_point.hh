#pragma once

extern fenix::Application* fenix::CreateApplication();

int main(int /* argc */, char** /* argv */)
{
    fenix::Log::Init();
    FX_CORE_WARN("Initialized Log!");

    auto app = fenix::CreateApplication();
    app->Run();
    delete app;
}
