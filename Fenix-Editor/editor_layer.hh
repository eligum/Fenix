#pragma once

#include <fenix/fenix.hh>

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
        OrthographicCameraController m_CameraController;

        Ref<VertexArray> m_SquareVA;
        Ref<Texture2D> m_Texture;
        Ref<Framebuffer> m_Framebuffer;
        uint32_t m_FPS;

        Ref<Scene> m_ActiveScene;
        Entity m_SquareEntity;
        Entity m_CameraEntity;
        Entity m_SecondCamera;

        bool m_PrimaryCamera = true;

        glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
        bool m_ViewportFocused = false, m_ViewportHovered = false;

        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
    };

} // namespace fenix
