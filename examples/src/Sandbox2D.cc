#include "Sandbox2D.hh"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

static constexpr float ASPECT_RATIO = 16.0f / 9.0f;

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(ASPECT_RATIO, true)
{}

void Sandbox2D::OnAttach()
{
    // Vertex array
    m_SquareVA = Fenix::VertexArray::Create();

    // Veretx buffer
    float squareVertices[4 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    Fenix::Ref<Fenix::VertexBuffer> squareVB;
    squareVB = Fenix::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
    Fenix::BufferLayout layout = {
        { Fenix::ShaderDataType::Float3, "a_Pos" },
    };
    squareVB->SetLayout(layout);
    m_SquareVA->AddVertexBuffer(squareVB);

    // Index buffer
    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Fenix::Ref<Fenix::IndexBuffer> squareIB;
    squareIB = Fenix::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Fenix::Shader::Create("examples/assets/shaders/flat_color.glsl");
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

    Fenix::Renderer::BeginScene(m_CameraController.GetCamera());

    m_FlatColorShader->Bind();
    m_FlatColorShader->SetFloat4("u_Color", m_SquareColor);

    Fenix::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Fenix::Renderer::EndScene();
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
