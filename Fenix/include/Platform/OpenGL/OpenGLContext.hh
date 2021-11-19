#pragma once

#include "Fenix/Renderer/GraphicsContext.hh"

struct GLFWwindow;

namespace fenix {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* window_handle);
        ~OpenGLContext();

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };

} // namespace fenix
