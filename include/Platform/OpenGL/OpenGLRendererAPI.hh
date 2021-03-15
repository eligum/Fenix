#pragma once

#include "Hazel/Renderer/RendererAPI.hh"

namespace Hazel {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void Init() override;

        void SetClearColor(const glm::vec4& color) override;
        void Clear() const override;

        void DrawIndexed(const Ref<VertexArray> vertex_array) override;
    };

}
