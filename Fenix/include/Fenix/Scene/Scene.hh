#pragma once

#include <entt/entt.hpp>

#include "Fenix/Core/Timestep.hh"

namespace Fenix {

    class Scene
    {
    public:
        Scene();
        ~Scene();

        entt::entity CreateEntity();
        void OnUpdate(Timestep ts);
    public:
        entt::registry m_Registry;
    };

} // namespace Fenix
