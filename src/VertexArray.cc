#include "Hazel/Renderer/VertexArray.hh"
#include "Hazel/Renderer/Renderer.hh"

#include "Platform/OpenGL/OpenGLVertexArray.hh"

namespace Hazel {

    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
        }

        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

} // namespace Hazel
