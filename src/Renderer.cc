#include "Hazel/Renderer/Renderer.hh"

namespace Hazel {

    // TODO: Initialize here shader uniforms, camera settings...
    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertex_array)
    {
        RenderCommand::DrawIndexed(vertex_array);
    }

} // namespace Hazel
