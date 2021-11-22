#include "fenix/renderer/vertex_array.hh"
#include "fenix/renderer/renderer.hh"
#include "platform/opengl/opengl_vertex_array.hh"

namespace fenix {

    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FENIX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
        }

        FENIX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

} // namespace fenix
