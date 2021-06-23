#pragma once

#include "Fenix/Core/Base.hh"
#include "Fenix/Scene/Scene.hh"
#include "Fenix/Scene/Entity.hh"

namespace Fenix {

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene>& scene);

        void SetContext(const Ref<Scene>& scene);
        void OnImGuiRender();
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);
    private:
        Ref<Scene> m_Context;
        Entity m_SelectionContext;
    };

} // namespace Fenix
