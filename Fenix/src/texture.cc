#include "fenix/renderer/texture.hh"
#include "fenix/renderer/renderer.hh"
#include "platform/opengl/opengl_texture.hh"

namespace fenix {

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FENIX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height);
        }

        FENIX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FENIX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(filepath);
        }

        FENIX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

} // namespace fenix
