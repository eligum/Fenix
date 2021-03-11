#pragma once

#include "Hazel/Renderer/RenderCommand.hh"

namespace Hazel {

    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertex_array);

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };

} // namespace Hazel
