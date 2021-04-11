#pragma once

#include "Fenix/Scene/Entity.hh"

namespace Fenix {

    class ScriptableEntity
    {
    public:
        virtual ~ScriptableEntity() = default;

        template <typename T>
        T& GetComponent()
            {
                return m_Entity.GetComponent<T>();
            }
    protected:
        virtual void OnCreate() {};
        virtual void OnDestroy() {};
        virtual void OnUpdate([[maybe_unused]] Timestep ts) {};
    private:
        Entity m_Entity;
        friend class Scene;
    };

} // namespace Fenix
