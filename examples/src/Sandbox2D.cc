#include "Sandbox2D.hh"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

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

    // Render - not really though
    Fenix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Fenix::RenderCommand::Clear();

    Fenix::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Fenix::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, 30.0f, { 1.0f, 1.0f }, { 0.8f, 0.3f, 0.2f, 1.0f });
    Fenix::Renderer2D::DrawQuad({ 0.5f, -0.4f }, { 0.8f, 0.5f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Fenix::Renderer2D::DrawQuad({ 0.5f,  0.5f, 0.1f }, { 0.8f, 0.8f }, m_Texture, 2.0f);
    Fenix::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Fenix::Event& e)
{
    m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}
