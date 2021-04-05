#include "Fenix/Scene/Entity.hh"

namespace Fenix {

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {
    }

} // namespace Fenix
