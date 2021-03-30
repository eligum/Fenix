#pragma once

#include "Fenix/Renderer/Camera.hh"
#include "Fenix/Renderer/Texture.hh"

namespace Fenix {

    class Renderer2D
    {
    public:
        static void Init();
        static void Shuttdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
        static void Flush();

        // Primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f);

        static void DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f);
        static void DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f);
    };

} // namespace Fenix
