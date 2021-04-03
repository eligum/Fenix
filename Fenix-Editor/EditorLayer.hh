#pragma once

#include <Fenix/Fenix.hh>

namespace Fenix {

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

        // TEMP
        Ref<VertexArray> m_SquareVA;
        Ref<Texture2D> m_Texture;
        Ref<Framebuffer> m_Framebuffer;
        uint32_t m_FPS;

        glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    };

} // namespace Fenix
