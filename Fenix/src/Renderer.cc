#include "Fenix/Renderer/Renderer.hh"
#include "Fenix/Renderer/Renderer2D.hh"

#include "Platform/OpenGL/OpenGLShader.hh"

namespace Fenix {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        // TEMP: This solution only works when rendering a single framebuffer
        RenderCommand::SetViewport(0, 0, width, height);
    }

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
        shader->SetMat4("u_ProjView", m_SceneData->ProjViewMatrix);
        shader->SetMat4("u_Transform", transform);

        vertex_array->Bind();
        RenderCommand::DrawIndexed(vertex_array);
        vertex_array->Unbind();
    }

} // namespace Fenix
