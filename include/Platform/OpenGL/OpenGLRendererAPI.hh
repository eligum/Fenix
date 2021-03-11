#pragma once

#include "Hazel/Renderer/RendererAPI.hh"

namespace Hazel {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void SetClearColor(const glm::vec4& color) override;
        void Clear() const override;

        void DrawIndexed(const std::shared_ptr<VertexArray> vertex_array) override;
    };

}
