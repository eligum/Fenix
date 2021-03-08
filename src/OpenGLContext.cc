#include "Platform/OpenGL/OpenGLContext.hh"
#include "Hazel/Base.hh"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel {

    OpenGLContext::OpenGLContext(GLFWwindow* window_handle)
        : m_WindowHandle(window_handle)
    {
        HZ_CORE_ASSERT(window_handle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        HZ_CORE_ASSERT(status, "Failed to initialize Glad!")
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

} // namespace Hazel
