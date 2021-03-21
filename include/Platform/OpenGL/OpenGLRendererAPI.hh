#pragma once

#include "Fenix/Renderer/RendererAPI.hh"

namespace Fenix {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void Init() override;
        void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;

        void SetClearColor(const glm::vec4& color) override;
        void Clear() const override;

        void DrawIndexed(const Ref<VertexArray> vertex_array) override;
    };

}
