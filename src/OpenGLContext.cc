#include "Platform/OpenGL/OpenGLContext.hh"
#include "Hazel/Core/Base.hh"

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
        HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

        HZ_CORE_INFO("------------");
        HZ_CORE_INFO("Vendor:   {0}", glGetString(GL_VENDOR));
        HZ_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
        HZ_CORE_INFO("Version:  {0}", glGetString(GL_VERSION));
        HZ_CORE_INFO("------------");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

} // namespace Hazel
