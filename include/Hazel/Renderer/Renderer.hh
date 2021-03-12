#pragma once

#include "Hazel/Renderer/RenderCommand.hh"
#include "Hazel/Renderer/Shader.hh"
#include "Hazel/Renderer/Camera.hh"

namespace Hazel {

    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array);

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 ProjViewMatrix;
        };

        static SceneData* m_SceneData;
    };

} // namespace Hazel
