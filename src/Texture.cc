#include "Fenix/Renderer/Texture.hh"

#include "Fenix/Renderer/Renderer.hh"
#include "Platform/OpenGL/OpenGLTexture.hh"

namespace Fenix {

    Ref<Texture2D> Texture2D::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(filepath);
        }

        FX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

} // namespace Fenix
