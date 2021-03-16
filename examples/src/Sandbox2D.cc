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
    m_SquareVA = Hazel::VertexArray::Create();

    // Veretx buffer
    float squareVertices[4 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    Hazel::Ref<Hazel::VertexBuffer> squareVB;
    squareVB = Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
    Hazel::BufferLayout layout = {
        { Hazel::ShaderDataType::Float3, "a_Pos" },
    };
    squareVB->SetLayout(layout);
    m_SquareVA->AddVertexBuffer(squareVB);

    // Index buffer
    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Hazel::Ref<Hazel::IndexBuffer> squareIB;
    squareIB = Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Hazel::Shader::Create("examples/assets/shaders/flat_color.glsl");
}

void Sandbox2D::OnDetach()
{
}


void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
    // Update
    m_CameraController.OnUpdate(ts);

    // Render - not really though
    Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Hazel::RenderCommand::Clear();

    Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

    m_FlatColorShader->Bind();
    m_FlatColorShader->SetFloat4("u_Color", m_SquareColor);

    Hazel::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Hazel::Renderer::EndScene();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
    m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}
