#pragma once

#include "Hazel/Renderer/Camera.hh"
#include "Hazel/Core/Timestep.hh"

#include "Hazel/Events/ApplicationEvent.hh"
#include "Hazel/Events/MouseEvent.hh"

namespace Hazel {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspect_ratio, bool enable_rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_ZoomLevel;
        OrthographicCamera m_Camera;

        bool m_Rotation;
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 1.0f;
        float m_CameraRotationSpeed = 120.0f;
    };

} // namespace Hazel
