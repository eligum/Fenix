#pragma once

extern fenix::Application* fenix::CreateApplication();

int main(int /* argc */, char** /* argv */)
{
    fenix::Log::Init();
    FX_CORE_INFO("Initialized Log.");
    FX_CORE_WARN("All output is being written to a file.");

    auto app = fenix::CreateApplication();
    app->Run();
    delete app;
}
