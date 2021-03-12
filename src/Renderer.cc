#include "Hazel/Renderer/Renderer.hh"

namespace Hazel {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    // TODO: Initialize here shader uniforms, camera settings...
    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ProjViewMatrix = camera.GetProjViewMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array)
    {
        shader->Bind();
        shader->SetMat4("u_ProjView", m_SceneData->ProjViewMatrix);

        vertex_array->Bind();
        RenderCommand::DrawIndexed(vertex_array);
        vertex_array->Unbind();
    }

} // namespace Hazel
