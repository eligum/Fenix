#include "Fenix/Fenix.hh"
#include "Fenix/Core/EntryPoint.hh"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.hh"

static constexpr float ASPECT_RATIO = 16.0f / 9.0f;

class ExampleLayer : public Fenix::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_CameraController(ASPECT_RATIO, true)
    {
        // VAO
        m_VertexArray = Fenix::VertexArray::Create();

        // VBO
        float vertices[3 * 7] = {
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };
        Fenix::Ref<Fenix::VertexBuffer> vertex_buffer;
        vertex_buffer = Fenix::VertexBuffer::Create(vertices, sizeof(vertices));
        Fenix::BufferLayout layout = {
            { Fenix::ShaderDataType::Float3, "a_Pos" },
            { Fenix::ShaderDataType::Float4, "a_Color" }
        };
        vertex_buffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertex_buffer);

        // EBO
        uint32_t indices[3] = { 0, 1, 2 };
        Fenix::Ref<Fenix::IndexBuffer> index_buffer;
        index_buffer = Fenix::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(index_buffer);

        m_VertexArray->Unbind();

        // VAO
        m_SquareVA = Fenix::VertexArray::Create();

        // VBO
        float sq_vertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };
        Fenix::Ref<Fenix::VertexBuffer> square_VB;
        square_VB = Fenix::VertexBuffer::Create(sq_vertices, sizeof(sq_vertices));
        Fenix::BufferLayout layout2 = {
            { Fenix::ShaderDataType::Float3, "a_Pos" },
            { Fenix::ShaderDataType::Float2, "a_TexCoord" }
        };
        square_VB->SetLayout(layout2);
        m_SquareVA->AddVertexBuffer(square_VB);

        // EBO
        uint32_t sq_indices[6] = { 0, 1, 2, 2, 3, 0 };
        Fenix::Ref<Fenix::IndexBuffer> square_IB;
        square_IB = Fenix::IndexBuffer::Create(sq_indices, sizeof(sq_indices) / sizeof(uint32_t));
        m_SquareVA->SetIndexBuffer(square_IB);

        m_Shader          = Fenix::Shader::Create("examples/assets/shaders/triangle.glsl");
        m_FlatColorShader = Fenix::Shader::Create("examples/assets/shaders/flat_color.glsl");
        m_TextureShader   = Fenix::Shader::Create("examples/assets/shaders/texture.glsl");

        m_TextureShader->Bind();
        m_TextureShader->SetInt("u_Texture", 0);

        m_Texture = Fenix::Texture2D::Create("examples/assets/textures/checkerboard.jpg");
        m_PikachuTex = Fenix::Texture2D::Create("examples/assets/textures/rainbow-eclipse.png");
    }

    void OnUpdate(Fenix::Timestep ts) override
    {
        // Update
        m_CameraController.OnUpdate(ts);

        // Render (not really)
        Fenix::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Fenix::RenderCommand::Clear();

        Fenix::Renderer::BeginScene(m_CameraController.GetCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        m_FlatColorShader->Bind();
        m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; ++y)
        {
            for (int x = 0; x < 20; ++x)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Fenix::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

        m_Texture->Bind(0);
        Fenix::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        m_PikachuTex->Bind(0);
        Fenix::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // Triangle
        // Fenix::Renderer::Submit(m_Shader, m_VertexArray);

        Fenix::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Fenix::Event& evt) override
    {
        m_CameraController.OnEvent(evt);

        // Fenix::EventDispatcher dispatcher(evt);
        // dispatcher.Dispatch<Fenix::KeyPressedEvent>(FENIX_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
    }

    bool OnKeyPressedEvent(Fenix::KeyPressedEvent& evt)
    {
        // FENIX_INFO("{0}", evt);
        return false;
    }
private:
    Fenix::Ref<Fenix::Shader> m_Shader;
    Fenix::Ref<Fenix::VertexArray> m_VertexArray;

    Fenix::Ref<Fenix::Shader> m_FlatColorShader, m_TextureShader;
    Fenix::Ref<Fenix::VertexArray> m_SquareVA;

    Fenix::Ref<Fenix::Texture2D> m_Texture;
    Fenix::Ref<Fenix::Texture2D> m_PikachuTex;

    Fenix::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

// This class inherits from Application
class Sandbox : public Fenix::Application
{
public:
    Sandbox()
        : Application("Sandbox 2D")
    {
        // PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox()
    {
    }
};

Fenix::Application* Fenix::CreateApplication()
{
    return new Sandbox;
}
