#pragma once

#include "fenix/renderer/renderer_API.hh"

namespace fenix {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void Init() override;
        void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;

        void SetClearColor(const glm::vec4& color) override;
        void Clear() const override;

        void DrawIndexed(const Ref<VertexArray> vertexArray, uint32_t indexCount = 0) override;
    };

}
