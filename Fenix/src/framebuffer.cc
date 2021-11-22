#include "fenix/renderer/framebuffer.hh"

#include "fenix/renderer/renderer.hh"
#include "platform/opengl/opengl_framebuffer.hh"

namespace fenix {

    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FENIX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
        }

        FENIX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}
