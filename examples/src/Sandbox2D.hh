#pragma once

#include "Fenix/Fenix.hh"

class Sandbox2D : public Fenix::Layer
{
public:
    Sandbox2D();
    ~Sandbox2D() = default;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(Fenix::Timestep ts) override;
    void OnEvent(Fenix::Event& e) override;
    void OnImGuiRender() override;
private:
    Fenix::OrthographicCameraController m_CameraController;

    // TEMP
    Fenix::Ref<Fenix::VertexArray> m_SquareVA;
    Fenix::Ref<Fenix::Shader> m_FlatColorShader;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
