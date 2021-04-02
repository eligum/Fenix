#include "Sandbox2D.hh"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

static constexpr float ASPECT_RATIO = 16.0f / 9.0f;

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(ASPECT_RATIO, true)
{}

void Sandbox2D::OnAttach()
{
    m_Texture = Fenix::Texture2D::Create("examples/assets/textures/checkerboard.jpg");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Fenix::Timestep ts)
{
    // Update
    m_CameraController.OnUpdate(ts);
    m_FPS = 1.0f / ts;

    // Render
    Fenix::Renderer2D::ResetStats();

    Fenix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Fenix::RenderCommand::Clear();

    Fenix::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Fenix::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, glm::radians(30.0f), { 1.0f, 1.0f }, { 0.8f, 0.3f, 0.2f, 1.0f });
    Fenix::Renderer2D::DrawQuad({ 0.5f, -0.4f }, { 0.8f, 0.5f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Fenix::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 8.0f, 8.0f }, m_Texture, 8.0f);
    Fenix::Renderer2D::EndScene();

    // Stress test
    Fenix::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (float y = -5.0f; y <= 5.0f; y += 0.5f)
    {
        for (float x = -5.0f; x <= 5.0f; x += 0.5f)
        {
            glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f };
            Fenix::Renderer2D::DrawRotatedQuad({ x, y, 0.1f }, glm::radians(10.0f), { 0.45f, 0.45f }, color);
        }
    }
    Fenix::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Fenix::Event& e)
{
    m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");

    auto stats = Fenix::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
    ImGui::Text("FPS: %d", m_FPS);

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}
