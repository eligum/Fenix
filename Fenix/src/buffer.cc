#include "fenix/renderer/buffer.hh"
#include "fenix/renderer/renderer.hh"

#include "platform/opengl/opengl_buffer.hh"

namespace fenix {

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FENIX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(size);
        }

        FENIX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FENIX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        FENIX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FENIX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, count);
        }

        FENIX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

} // namespace fenix
