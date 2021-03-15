#include "Platform/OpenGL/OpenGLRendererAPI.hh"

#include <glad/glad.h>

namespace Hazel {

    void OpenGLRendererAPI::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> vertex_array)
    {
        glDrawElements(GL_TRIANGLES, vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

} // namespace Hazel
