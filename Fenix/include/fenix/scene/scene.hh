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

        void OnUpdate(Timestep ts);
        void OnViewportResize(uint32_t width, uint32_t height);
    private:
        entt::registry m_Registry;
        uint32_t m_ViewportHeight = 0, m_ViewportWidth = 0;

        friend class Entity;
        friend class SceneHierarchyPanel;
    };

} // namespace fenix
