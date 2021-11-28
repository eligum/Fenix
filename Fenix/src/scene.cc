#include "fenix/scene/scene.hh"
#include "fenix/scene/components.hh"
#include "fenix/renderer/renderer_2D.hh"
#include "fenix/scene/entity.hh"

namespace fenix {

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { m_Registry.create(), this };
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = (name.empty()) ? "Undefined" : name;

        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.destroy(entity);
    }

    void Scene::OnUpdate(Timestep ts)
    {
        // Update scripts
        {
            m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc) {
                // TODO: Move to Scene::OnScenePlay
                if (nsc.Instance == nullptr)
                {
                    nsc.Instance = nsc.InstantiateScript();
                    nsc.Instance->m_Entity = Entity{ entity, this };
                    nsc.Instance->OnCreate();
                }

                nsc.Instance->OnUpdate(ts);
            });
        }

        // Render sprites
        Camera* main_camera = nullptr;
        glm::mat4 camera_transform;
        {
            auto view = m_Registry.view<TransformComponent, CameraComponent>();
            for (auto entity : view)
            {
                auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

                if (camera.Primary)
                {
                    main_camera = &camera.Camera;
                    camera_transform = transform.GetTransform();
                    break;
                }
            }
        }

        if (main_camera)
        {
            Renderer2D::BeginScene(*main_camera, camera_transform);

            auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity : group)
            {
                auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
                Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
            }

            Renderer2D::EndScene();
        }
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        // Resize non-fixed-aspect-ratio cameras
        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& camera_component = view.get<CameraComponent>(entity);
            if (!camera_component.FixedAspectRatio)
                camera_component.Camera.SetViewportSize(width, height);
        }
    }

    template <typename T>
    void Scene::OnComponentAddition(Entity entity, T& component)
    {
        // static_assert(false);
    }

    template<>
    void Scene::OnComponentAddition<TagComponent>(Entity entity, TagComponent& component)
    {
    }

    template<>
    void Scene::OnComponentAddition<TransformComponent>(Entity entity, TransformComponent& component)
    {
    }

    template<>
    void Scene::OnComponentAddition<CameraComponent>(Entity entity, CameraComponent& component)
    {
        component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportWidth);
    }

    template<>
    void Scene::OnComponentAddition<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {
    }

    template<>
    void Scene::OnComponentAddition<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
    {
    }

} // namespace fenix
