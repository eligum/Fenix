#include "Hazel/Hazel.hh"

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer()
        : Layer("Example") {}

    void OnUpdate() override
    {
        // HZ_INFO("ExampleLayer::Update");
        if (Hazel::Input::IsKeyPressed(Hazel::Key::Tab))
            HZ_TRACE("Tab is being pressed!");
    }

    void OnEvent(Hazel::Event& e) override
    {
        // HZ_TRACE("{0}", e);
    }
};

class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new Hazel::ImGuiLayer());
    }

    ~Sandbox() {}
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sandbox;
}
