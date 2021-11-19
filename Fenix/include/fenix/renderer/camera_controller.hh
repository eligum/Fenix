#pragma once

#include "fenix/renderer/camera.hh"
#include "fenix/core/timestep.hh"
#include "fenix/events/application_event.hh"
#include "fenix/events/mouse_event.hh"

namespace fenix {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspect_ratio, bool enable_rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        void OnResize(float width, float height);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }
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
        float m_CameraTranslationSpeed = 2.0f;
        float m_CameraRotationSpeed = 120.0f;
    };

} // namespace fenix
