#include "LinuxWindow.hh"
#include "../Base.hh"

namespace flyCore {

    static uint8_t s_GLFWWindowCount = 0;

    Window* Window::Create(const WindowProps& props)
    {
        return new LinuxWindow(props);
    }

    LinuxWindow::LinuxWindow(const WindowProps& props)
    {
        Init(props);
    }

    LinuxWindow::~LinuxWindow()
    {
        Shutdown();
    }

    void LinuxWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        FLY_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0)
        {
            int success = glfwInit();
            FLY_CORE_ASSERT(success, "Failed to initialize GLFW!")
        }

        m_Window = glfwCreateWindow(static_cast<int>(props.Width),
                                    static_cast<int>(props.Height),
                                    m_Data.Title.c_str(), nullptr, nullptr);
        ++s_GLFWWindowCount;
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void LinuxWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        --s_GLFWWindowCount;
        if (s_GLFWWindowCount == 0)
            glfwTerminate();
    }

    void LinuxWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void LinuxWindow::SetVSync(bool enabled)
    {
        (enabled) ? glfwSwapInterval(1) : glfwSwapInterval(0);
        m_Data.VSync = enabled;
    }

    bool LinuxWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

} // namespace flyCore
