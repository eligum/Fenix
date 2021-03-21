#include "Platform/OpenGL/OpenGLContext.hh"
#include "Fenix/Core/Base.hh"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Fenix {

    OpenGLContext::OpenGLContext(GLFWwindow* window_handle)
        : m_WindowHandle(window_handle)
    {
        FX_CORE_ASSERT(window_handle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        FX_CORE_ASSERT(status, "Failed to initialize Glad!");

        FX_CORE_INFO("------------");
        FX_CORE_INFO("Vendor:   {0}", glGetString(GL_VENDOR));
        FX_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
        FX_CORE_INFO("Version:  {0}", glGetString(GL_VERSION));
        FX_CORE_INFO("------------");

        FX_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Fenix requires at least OpenGL version 4.5");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

} // namespace Fenix
