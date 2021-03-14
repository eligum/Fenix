#pragma once

#include "Hazel/Renderer/RendererAPI.hh"

namespace Hazel {

    class RenderCommand
    {
    public:
        static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }

        static void Clear()
        {
            s_RendererAPI->Clear();
        }

        static void DrawIndexed(const Ref<VertexArray>& vertex_array)
        {
            s_RendererAPI->DrawIndexed(vertex_array);
        }
    private:
        static RendererAPI* s_RendererAPI;
    };

} // namespace Hazel
