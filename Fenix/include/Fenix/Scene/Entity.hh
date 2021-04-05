#pragma once

#include "Fenix/Scene/Scene.hh"
#include <entt/entt.hpp>
#include "Fenix/Core/Base.hh"

namespace Fenix {

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
                FX_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
                return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
            }

        template <typename T>
        T& GetComponent()
            {
                FX_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
                return m_Scene->m_Registry.get<T>(m_EntityHandle);
            }

        template <typename T>
        bool RemoveComponent()
            {
                FX_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
                return m_Scene->m_Registry.remove<T>(m_EntityHandle);
            }

        operator bool() const { return m_Scene->m_Registry.valid(m_EntityHandle); }

    private:
        entt::entity m_EntityHandle = entt::null;
        Scene* m_Scene = nullptr; // Should be a weak pointer
    };

} // namespace Fenix
