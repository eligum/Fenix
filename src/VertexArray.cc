#include "Fenix/Renderer/VertexArray.hh"
#include "Fenix/Renderer/Renderer.hh"

#include "Platform/OpenGL/OpenGLVertexArray.hh"

namespace Fenix {

    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
        }

        FX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

} // namespace Fenix
