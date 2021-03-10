#include "Hazel/Core/Application.hh"
#include "Hazel/Core/Log.hh"
#include "Hazel/Core/Events/ApplicationEvent.hh"

// TEMP: Temporary
#include <glad/glad.h>

namespace Hazel {

    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Bool:   return GL_BOOL;
            case ShaderDataType::None:   break;
        }
        HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    Application::Application()
    {
        HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[3 * 7] = {
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };
        uint32_t indices[3] = { 0, 1, 2 };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Pos" },
                { ShaderDataType::Float4, "a_Color" }
            };
            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = m_VertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalize ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  reinterpret_cast<const void*>(element.Offset));
            index++;
        }

        glBindVertexArray(0);

        std::string vertexSrc = R"(
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

        std::string fragmentSrc = R"(
            #version 330 core
            in vec3 v_Pos;
            in vec4 v_Color;
            out vec4 color;
            void main()
            {
                color = v_Color;
            }
        )";

        m_Shader.reset(new OpenGLShader("plain_color", vertexSrc, fragmentSrc));
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
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
