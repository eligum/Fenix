#pragma once

#include <entt/entt.hpp>

#include "fenix/scene/scene.hh"
#include "fenix/core/base.hh"

namespace fenix {

    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& other) = default;

        template <typename T>
        bool HasComponent()
            {
                return m_Scene->m_Registry.has<T>(m_EntityHandle);
            }

        template <typename T, typename... Args>
        T& AddComponent(Args&&... args)
            {
                FENIX_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
                return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
            }

        template <typename T>
        T& GetComponent()
            {
                FENIX_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
                return m_Scene->m_Registry.get<T>(m_EntityHandle);
            }

        template <typename T>
        bool RemoveComponent()
            {
                FENIX_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
                return m_Scene->m_Registry.remove<T>(m_EntityHandle);
            }

        operator bool() const { return m_Scene->m_Registry.valid(m_EntityHandle); }

    private:
        entt::entity m_EntityHandle = entt::null;
        Scene* m_Scene = nullptr; // Should be a weak pointer
    };

} // namespace fenix
