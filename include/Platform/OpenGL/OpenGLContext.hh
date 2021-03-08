#pragma once

#include "Hazel/Renderer/GraphicsContext.hh"

struct GLFWwindow;

namespace Hazel {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* window_handle);

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };

} // namespace Hazel
