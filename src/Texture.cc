#include "Fenix/Renderer/Texture.hh"

#include "Fenix/Renderer/Renderer.hh"
#include "Platform/OpenGL/OpenGLTexture.hh"

namespace Fenix {

    Ref<Texture2D> Texture2D::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(filepath);
        }

        FX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height);
        }

        FX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

} // namespace Fenix
