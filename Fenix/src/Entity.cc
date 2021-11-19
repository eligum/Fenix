#include "Fenix/Scene/Entity.hh"

namespace fenix {

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {
    }

} // namespace fenix
