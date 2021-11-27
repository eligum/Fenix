#pragma once

#include <glm/glm.hpp>
#include <string>

#include "fenix/scene/scene_camera.hh"
#include "fenix/scene/scriptable_entity.hh"

namespace fenix {

    struct TagComponent
    {
        std::string Tag {"Unknown"};

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag)
            : Tag(tag) {}
    };

    struct TransformComponent
    {
        glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation    = { 0.0f, 0.0f, 0.0f }; // Stored in radiants
        glm::vec3 Scale       = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& translation)
            : Translation(translation) {}

        glm::mat4 GetTransform() const
        {
            glm::mat4 tg {1.0f};
            tg = glm::translate(tg, Translation);
            tg = glm::rotate(tg, Rotation.x, { 1, 0, 0 });
            tg = glm::rotate(tg, Rotation.y, { 0, 1, 0 });
            tg = glm::rotate(tg, Rotation.z, { 0, 0, 1 });
            tg = glm::scale(tg, Scale);
            return tg;
        }
    };

    struct SpriteRendererComponent
    {
        glm::vec4 Color {1.0f, 1.0f, 1.0f, 1.0f};

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
