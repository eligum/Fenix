#include "Firefly/Firefly.hh"

class ExampleLayer : public flyCore::Layer
{
public:
    ExampleLayer()
        : Layer("Example") {}

    void OnUpdate() override
    {
        // FLY_INFO("ExampleLayer::Update");
    }

    void OnEvent(flyCore::Event& e) override
    {
        FLY_TRACE("{0}", e);
    }
};

class Sandbox : public flyCore::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new flyCore::ImGuiLayer());
    }

    ~Sandbox() {}
};

flyCore::Application* flyCore::CreateApplication()
{
    return new Sandbox;
}
