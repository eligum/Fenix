#pragma once

#include "fenix/renderer/render_command.hh"
#include "fenix/renderer/shader.hh"
#include "fenix/renderer/camera.hh"

namespace fenix {

    class Renderer
    {
    public:
        static void Init();
        static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const Ref<Shader>&      shader,
                           const Ref<VertexArray>& vertex_array,
                           const glm::mat4&        transform = glm::mat4(1.0f));

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 ProjViewMatrix;
        };

        static SceneData* m_SceneData;
    };

} // namespace fenix
