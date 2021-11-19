#pragma once

#include <glm/glm.hpp>

#include "fenix/renderer/vertex_array.hh"

namespace fenix {

    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1,
        };
    public:
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() const = 0;

        virtual void DrawIndexed(const Ref<VertexArray> vertexArray, uint32_t indexCount = 0) = 0;

        static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };

} // namespace fenix
