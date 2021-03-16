#include "Hazel/Hazel.hh"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

static constexpr float ASPECT_RATIO = 1600.0f / 900.0f;

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_CameraController(ASPECT_RATIO, true)
    {
        // VAO
        m_TriangleVA.reset(Hazel::VertexArray::Create());

        // VBO
        float vertices[3 * 7] = {
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };
        Hazel::Ref<Hazel::VertexBuffer> vertex_buffer;
        vertex_buffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
        Hazel::BufferLayout layout = {
            { Hazel::ShaderDataType::Float3, "a_Pos" },
            { Hazel::ShaderDataType::Float4, "a_Color" }
        };
        vertex_buffer->SetLayout(layout);
        m_TriangleVA->AddVertexBuffer(vertex_buffer);

        // EBO
        uint32_t indices[3] = { 0, 1, 2 };
        Hazel::Ref<Hazel::IndexBuffer> index_buffer;
        index_buffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_TriangleVA->SetIndexBuffer(index_buffer);

        m_TriangleVA->Unbind();

        // VAO
        m_SquareVA.reset(Hazel::VertexArray::Create());

        // VBO
        float sq_vertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };
        Hazel::Ref<Hazel::VertexBuffer> square_VB;
        square_VB.reset(Hazel::VertexBuffer::Create(sq_vertices, sizeof(sq_vertices)));
        Hazel::BufferLayout layout2 = {
            { Hazel::ShaderDataType::Float3, "a_Pos" },
            { Hazel::ShaderDataType::Float2, "a_TexCoord" }
        };
        square_VB->SetLayout(layout2);
        m_SquareVA->AddVertexBuffer(square_VB);

        // EBO
        uint32_t sq_indices[6] = { 0, 1, 2, 2, 3, 0 };
        Hazel::Ref<Hazel::IndexBuffer> square_IB;
        square_IB.reset(Hazel::IndexBuffer::Create(sq_indices, sizeof(sq_indices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(square_IB);

        m_Shader          = Hazel::Shader::Create("examples/assets/shaders/triangle.glsl");
        m_FlatColorShader = Hazel::Shader::Create("examples/assets/shaders/flat_color.glsl");
        m_TextureShader   = Hazel::Shader::Create("examples/assets/shaders/texture.glsl");

        m_TextureShader->Bind();
        m_TextureShader->SetInt("u_Texture", 0);

        m_Texture = Hazel::Texture2D::Create("examples/assets/textures/checkerboard.jpg");
        m_PikachuTex = Hazel::Texture2D::Create("examples/assets/textures/rainbow-eclipse.png");
    }

    void OnUpdate(Hazel::Timestep ts) override
    {
        // Update
        m_CameraController.OnUpdate(ts);

        // Render (not really)
        Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Hazel::RenderCommand::Clear();


        Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        m_FlatColorShader->Bind();
        m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; ++y)
        {
            for (int x = 0; x < 20; ++x)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Hazel::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

        m_Texture->Bind(0);
        Hazel::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        m_PikachuTex->Bind(0);
        Hazel::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // Triangle
        // Hazel::Renderer::Submit(m_Shader, m_TriangleVA);

        Hazel::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Hazel::Event& evt) override
    {
        m_CameraController.OnEvent(evt);

        // Hazel::EventDispatcher dispatcher(evt);
        // dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
    }

    bool OnKeyPressedEvent(Hazel::KeyPressedEvent& evt)
    {
        // HZ_INFO("{0}", evt);
        return false;
    }
private:
    Hazel::Ref<Hazel::Shader> m_Shader;
    Hazel::Ref<Hazel::VertexArray> m_TriangleVA;

    Hazel::Ref<Hazel::Shader> m_FlatColorShader, m_TextureShader;
    Hazel::Ref<Hazel::VertexArray> m_SquareVA;

    Hazel::Ref<Hazel::Texture2D> m_Texture;
    Hazel::Ref<Hazel::Texture2D> m_PikachuTex;

    Hazel::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};


// This class inherits from Application
class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {
    }
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sandbox;
}
