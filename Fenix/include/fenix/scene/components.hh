#pragma once

#include <glm/mat4x4.hpp>
#include <string>

#include "fenix/scene/scene_camera.hh"
#include "fenix/scene/scriptable_entity.hh"

namespace fenix {

    struct TransformComponent
    {
        glm::mat4 Transform{ 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::mat4& transform)
            : Transform(transform) {}
    };

    struct TagComponent
    {
        std::string Tag{ "Unknown" };

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag)
            : Tag(tag) {}
    };

    struct SpriteRendererComponent
    {
        glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent&) = default;
        SpriteRendererComponent(const glm::vec4& color)
            : Color(color) {}
    };

    struct CameraComponent
    {
        SceneCamera Camera;
        bool Primary = true; // TODO: Think about moving to Scene.
        bool FixedAspectRatio = false;

        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;
    };

    struct NativeScriptComponent
    {
        ScriptableEntity* Instance = nullptr;

        // Function pointers
        ScriptableEntity* (*InstantiateScript)();
        void              (*DestroyScript)(NativeScriptComponent*);

        template <typename T>
        void Bind()
        {
            InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
            DestroyScript     = [](NativeScriptComponent* self) { delete self->Instance; self->Instance = nullptr; };
        }
    };

} // namespace fenix
