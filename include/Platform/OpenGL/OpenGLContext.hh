#pragma once

#include "Fenix/Renderer/GraphicsContext.hh"

struct GLFWwindow;

namespace Fenix {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* window_handle);

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };

} // namespace Fenix
