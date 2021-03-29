#include "Fenix/Renderer/Buffer.hh"
#include "Fenix/Renderer/Renderer.hh"

#include "Platform/OpenGL/OpenGLBuffer.hh"

namespace Fenix {

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(count);
        }

        FX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, count);
        }

        FX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, count);
        }

        FX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

} // namespace Fenix
