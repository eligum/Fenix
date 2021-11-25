#pragma once

#include "fenix/scene/entity.hh"

namespace fenix {

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
        virtual void OnUpdate(Timestep ts) {};

    private:
        Entity m_Entity;
        friend class Scene; // Give Scene access to the private members of this class
    };

} // namespace fenix
