#pragma once

#include "fenix/renderer/renderer_API.hh"

namespace fenix {

    class RenderCommand
    {
    public:
        static void Init()
        {
            s_RendererAPI->Init();
        }

        static void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
        {
            s_RendererAPI->SetViewport(x, y, w, h);
        }

        static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }

        static void Clear()
        {
            s_RendererAPI->Clear();
        }

        static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
        {
            s_RendererAPI->DrawIndexed(vertexArray, indexCount);
        }
    private:
        static RendererAPI* s_RendererAPI;
    };

} // namespace fenix
