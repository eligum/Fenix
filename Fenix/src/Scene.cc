#include "Fenix/Scene/Scene.hh"

#include "Fenix/Scene/Components.hh"
#include "Fenix/Renderer/Renderer2D.hh"
#include "Fenix/Scene/Entity.hh"

namespace Fenix {

    Scene::Scene()
    {
        // entt::entity entity = m_Registry.create();
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { m_Registry.create(), this };
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = (name.empty()) ? "Unnamed Entity" : name;

        return entity;
    }

    void Scene::OnUpdate(Timestep ts)
    {
        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            const auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
            Renderer2D::DrawQuad(transform.Transform, sprite.Color);
        }
    }

} // namespace Fenix
