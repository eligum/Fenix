#include "Fenix/Scene/Scene.hh"

#include <glm/mat4x4.hpp>
#include "Fenix/Scene/Components.hh"

namespace Fenix {

    Scene::Scene()
    {
        // entt::entity entity = m_Registry.create();
    }

    Scene::~Scene()
    {
    }

    entt::entity Scene::CreateEntity()
    {
        return m_Registry.create();
    }

    void Scene::OnUpdate(Timestep ts)
    {

    }

} // namespace Fenix
