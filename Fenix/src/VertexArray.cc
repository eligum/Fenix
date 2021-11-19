#include "Fenix/Renderer/VertexArray.hh"
#include "Fenix/Renderer/Renderer.hh"

#include "Platform/OpenGL/OpenGLVertexArray.hh"

namespace fenix {

    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
        }

        FX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

} // namespace fenix
