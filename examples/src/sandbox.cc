#include "Firefly/Firefly.hh"

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer()
        : Layer("Example") {}

    void OnUpdate() override
    {
        // FLY_INFO("ExampleLayer::Update");
    }

    void OnEvent(Hazel::Event& e) override
    {
        FLY_TRACE("{0}", e);
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
