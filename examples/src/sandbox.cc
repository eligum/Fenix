#include "Hazel/Hazel.hh"

#include "imgui.h"

constexpr float ASPECT_RATIO = 16.0f / 9.0f;
constexpr float HEIGHT = 2.0f;

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-0.5f * HEIGHT * ASPECT_RATIO, 0.5f * HEIGHT * ASPECT_RATIO, -0.5f * HEIGHT, 0.5f * HEIGHT),
          m_CameraPos(0.0f), m_CameraAngle(0.0f)
    {
        // VAO
        m_TriangleVA.reset(Hazel::VertexArray::Create());

        // VBO
        float vertices[3 * 7] = {
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };
        std::shared_ptr<Hazel::VertexBuffer> vertex_buffer;
        vertex_buffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
        Hazel::BufferLayout layout = {
            { Hazel::ShaderDataType::Float3, "a_Pos" },
            { Hazel::ShaderDataType::Float4, "a_Color" }
        };
        vertex_buffer->SetLayout(layout);
        m_TriangleVA->AddVertexBuffer(vertex_buffer);

        // EBO
        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<Hazel::IndexBuffer> index_buffer;
        index_buffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_TriangleVA->SetIndexBuffer(index_buffer);

        m_TriangleVA->Unbind();

        // VAO
        m_SquareVA.reset(Hazel::VertexArray::Create());

        // VBO
        float sq_vertices[4 * 3] = {
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f,
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f
        };
        std::shared_ptr<Hazel::VertexBuffer> square_VB;
        square_VB.reset(Hazel::VertexBuffer::Create(sq_vertices, sizeof(sq_vertices)));
        Hazel::BufferLayout layout2 = {
            { Hazel::ShaderDataType::Float3, "a_Pos" }
        };
        square_VB->SetLayout(layout2);
        m_SquareVA->AddVertexBuffer(square_VB);

        // EBO
        uint32_t sq_indices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<Hazel::IndexBuffer> square_IB;
        square_IB.reset(Hazel::IndexBuffer::Create(sq_indices, sizeof(sq_indices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(square_IB);

        // Create and compile shaders
        std::string vertex_src = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Pos;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ProjView;

            out vec4 v_Color;

            void main()
            {
                v_Color = a_Color;
                gl_Position = u_ProjView * vec4(a_Pos , 1.0);
            }
        )";

        std::string fragment_src = R"(
            #version 330 core

            in vec4 v_Color;

            out vec4 color;

            void main()
            {
                color = v_Color;
            }
        )";

        m_Shader.reset(Hazel::Shader::Create("vertex-based-color", vertex_src, fragment_src));

        std::string blue_shader_vert_src = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Pos;

            uniform mat4 u_ProjView;

            void main()
            {
                gl_Position = u_ProjView * vec4(a_Pos , 1.0);
            }
        )";

        std::string blue_shader_frag_src = R"(
            #version 330 core

            out vec4 color;

            void main()
            {
                color = vec4(0.33, 0.67, 1.00, 1.0);
            }
        )";

        m_BlueShader.reset(Hazel::Shader::Create("blue-shader", blue_shader_vert_src, blue_shader_frag_src));
    }

    void OnUpdate() override
    {
        if (Hazel::Input::IsKeyPressed(Hazel::Key::A))
            m_CameraPos.x -= 0.002f;
        if (Hazel::Input::IsKeyPressed(Hazel::Key::D))
            m_CameraPos.x += 0.002f;

        Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Hazel::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPos);
        m_Camera.SetRotation(m_CameraAngle);

        Hazel::Renderer::BeginScene(m_Camera);

        Hazel::Renderer::Submit(m_BlueShader, m_SquareVA);
        Hazel::Renderer::Submit(m_Shader, m_TriangleVA);

        Hazel::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        // ImGui::Begin("Test");
        // ImGui::Text("Hello World!");
        // ImGui::End();
     }

    void OnEvent(Hazel::Event& evt) override
    {
        // HZ_TRACE("{0}", e);
        // Hazel::EventDispatcher dispatcher(evt);
        // dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
    }

    bool OnKeyPressedEvent(Hazel::KeyPressedEvent& evt)
    {
        // if (evt.GetKeyCode() == Hazel::Key::A)
        //     m_CameraPos.x += 0.1f;

        // return false;
    }
private:
    std::shared_ptr<Hazel::Shader> m_Shader;
    std::shared_ptr<Hazel::VertexArray> m_TriangleVA;

    std::shared_ptr<Hazel::Shader> m_BlueShader;
    std::shared_ptr<Hazel::VertexArray> m_SquareVA;

    Hazel::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPos;
    float m_CameraAngle;
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
