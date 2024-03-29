#include "platform/opengl/opengl_context.hh"
#include "fenix/core/base.hh"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace fenix {

    OpenGLContext::OpenGLContext(GLFWwindow* window_handle)
        : m_WindowHandle(window_handle)
    {
        FENIX_CORE_ASSERT(window_handle, "Window handle is null!");
    }

    OpenGLContext::~OpenGLContext()
    {
        glfwTerminate();
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        FENIX_CORE_ASSERT(status, "Failed to initialize Glad!");

        FENIX_CORE_INFO("------------");
        FENIX_CORE_INFO("Vendor:   {0}", glGetString(GL_VENDOR));
        FENIX_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
        FENIX_CORE_INFO("Version:  {0}", glGetString(GL_VERSION));
        FENIX_CORE_INFO("------------");

        FENIX_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Fenix requires at least OpenGL version 4.5");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

} // namespace fenix
