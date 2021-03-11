#include "Hazel/Core/Application.hh"
#include "Hazel/Core/Log.hh"
#include "Hazel/Core/Events/ApplicationEvent.hh"

// TEMP: Temporary
#include <glad/glad.h>
#include "Hazel/Renderer/Renderer.hh"

namespace Hazel {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        // VAO
        m_TriangleVA.reset(VertexArray::Create());

        // VBO
        float vertices[3 * 7] = {
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };
        std::shared_ptr<VertexBuffer> vertex_buffer;
        vertex_buffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Pos" },
            { ShaderDataType::Float4, "a_Color" }
        };
        vertex_buffer->SetLayout(layout);
        m_TriangleVA->AddVertexBuffer(vertex_buffer);

        // EBO
        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> index_buffer;
        index_buffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_TriangleVA->SetIndexBuffer(index_buffer);

        // VAO
        m_SquareVA.reset(VertexArray::Create());

        // VBO
        float sq_vertices[4 * 3] = {
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f,
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f
        };
        std::shared_ptr<VertexBuffer> square_VB;
        square_VB.reset(VertexBuffer::Create(sq_vertices, sizeof(sq_vertices)));
        BufferLayout layout2 = {
            { ShaderDataType::Float3, "a_Pos" }
        };
        square_VB->SetLayout(layout2);
        m_SquareVA->AddVertexBuffer(square_VB);

        // EBO
        uint32_t sq_indices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> square_IB;
        square_IB.reset(IndexBuffer::Create(sq_indices, sizeof(sq_indices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(square_IB);

        // Create and compile shaders
        std::string vertex_src = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Pos;
            layout(location = 1) in vec4 a_Color;
            out vec3 v_Pos;
            out vec4 v_Color;
            void main()
            {
                v_Pos = a_Pos;
                v_Color = a_Color;
                gl_Position = vec4(a_Pos , 1.0);
            }
        )";

        std::string fragment_src = R"(
            #version 330 core
            in vec3 v_Pos;
            in vec4 v_Color;
            out vec4 color;
            void main()
            {
                color = v_Color;
            }
        )";

        m_Shader.reset(new OpenGLShader("pos-based-color", vertex_src, fragment_src));

        std::string blue_shader_vert_src = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Pos;
            void main()
            {
                gl_Position = vec4(a_Pos , 1.0);
            }
        )";

        std::string blue_shader_frag_src = R"(
            #version 330 core
            out vec4 color;
            void main()
            {
                color = vec4(0.1, 0.2, 0.8, 1.0);
            }
        )";

        m_BlueShader.reset(new OpenGLShader("blue-shader", blue_shader_vert_src, blue_shader_frag_src));

    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& evt)
    {
        EventDispatcher dispatcher(evt);
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

        HZ_CORE_TRACE("{0}", evt);

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(evt);
            if (evt.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }

    bool Application::OnWindowClose(WindowCloseEvent& evt)
    {
        m_Running = false;
        return true;
    }

    void Application::Run()
    {
        while (m_Running)
        {
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            RenderCommand::Clear();

            Renderer::BeginScene();

            m_BlueShader->Bind();
            Renderer::Submit(m_SquareVA);

            m_Shader->Bind();
            Renderer::Submit(m_TriangleVA);

            Renderer::EndScene();

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->BeginDraw();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->EndDraw();

            m_Window->OnUpdate();
        }
    }

} // namespace Hazel
