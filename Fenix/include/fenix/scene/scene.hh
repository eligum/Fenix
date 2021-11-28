#pragma once

#include <entt/entt.hpp>

#include "fenix/core/timestep.hh"

namespace fenix {

    class Entity; // Forward declaration

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = "");
        void DestroyEntity(Entity entity);

        void OnUpdate(Timestep ts);
        void OnViewportResize(uint32_t width, uint32_t height);
    private:
        template <typename T>
        void OnComponentAddition(Entity entity, T& component);
    private:
        entt::registry m_Registry;
        uint32_t m_ViewportHeight = 0;
        uint32_t m_ViewportWidth = 0;

        friend class Entity;
        friend class SceneHierarchyPanel;
    };

} // namespace fenix
