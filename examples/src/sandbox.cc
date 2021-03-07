#include "Hazel/Hazel.hh"

#include "imgui.h"

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

    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!");
        ImGui::End();
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
    }

    ~Sandbox() {}
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sandbox;
}
