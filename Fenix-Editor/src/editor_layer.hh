#pragma once

#include <fenix/fenix.hh>
#include "panels/scene_hierarchy_panel.hh"

namespace fenix {

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        ~EditorLayer() = default;

        void OnAttach() override;
        void OnDetach() override;

        void OnUpdate(Timestep ts) override;
        void OnEvent(Event& e) override;
        void OnImGuiRender() override;

    private:
        bool OnKeyPressed(KeyPressedEvent& e);
        void NewScene();
        void OpenScene();
        void SaveSceneAs();

    private:
        OrthographicCameraController m_CameraController;

        Ref<VertexArray> m_SquareVA;
        Ref<Texture2D> m_Texture;
        Ref<Framebuffer> m_Framebuffer;
        uint32_t m_FPS;

        Ref<Scene> m_ActiveScene;
        Entity m_SquareEntity;
        Entity m_CameraEntity;
        Entity m_SecondCamera;

        bool m_ViewportFocused = false;
        bool m_ViewportHovered = false;

        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

        // Panels
        SceneHierarchyPanel m_SceneHierarchyPanel;
    };

} // namespace fenix
