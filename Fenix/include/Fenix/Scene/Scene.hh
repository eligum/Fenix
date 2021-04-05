#pragma once

#include <entt/entt.hpp>

#include "Fenix/Core/Timestep.hh"

namespace Fenix {

    class Entity; // Forward declaration

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = "");
        void OnUpdate([[maybe_unused]] Timestep ts);
    private:
        entt::registry m_Registry;

        friend class Entity;
    };

} // namespace Fenix
