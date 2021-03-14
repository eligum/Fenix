#include "Hazel/Renderer/Renderer.hh"

#include "Platform/OpenGL/OpenGLShader.hh"

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

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("u_ProjView", m_SceneData->ProjViewMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("u_Transform", transform);

        vertex_array->Bind();
        RenderCommand::DrawIndexed(vertex_array);
        vertex_array->Unbind();
    }

} // namespace Hazel
