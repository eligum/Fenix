#pragma once

#include <glm/glm.hpp>

#include "Hazel/Renderer/VertexArray.hh"

namespace Hazel {

    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1,
        };
    public:
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() const = 0;

        virtual void DrawIndexed(const Ref<VertexArray> vertex_array) = 0;

        static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };

} // namespace Hazel
