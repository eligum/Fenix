#include "fenix/renderer/camera_controller.hh"
#include "fenix/core/input.hh"

namespace fenix {

    OrthographicCameraController::OrthographicCameraController(float aspect_ratio, bool enable_rotation)
        : m_AspectRatio(aspect_ratio), m_ZoomLevel(1.0f),
          m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
          m_Rotation(enable_rotation)
    {}

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyPressed(key::A))
        {
            m_CameraPosition.x -= glm::cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y -= glm::sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(key::D))
        {
            m_CameraPosition.x += glm::cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y += glm::sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }

        if (Input::IsKeyPressed(key::W))
        {
            m_CameraPosition.x += -glm::sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y += glm::cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(key::S))
        {
            m_CameraPosition.x -= -glm::sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y -= glm::cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }
        if (m_Rotation)
        {
            if (Input::IsKeyPressed(key::Q))
                m_CameraRotation += m_CameraRotationSpeed * ts;
            else if (Input::IsKeyPressed(key::E))
                m_CameraRotation -= m_CameraRotationSpeed * ts;

            if (m_CameraRotation > 180.0f)
                m_CameraRotation -= 360.0f;
            else if (m_CameraRotation < -180.0f)
                m_CameraRotation += 360.0f;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(FENIX_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    }

    void OrthographicCameraController::OnResize(float width, float height)
    {
        m_AspectRatio = width / height;
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::min(20.0f, std::max(0.25f, m_ZoomLevel)); // Clamp to [0.25, 20.0f]
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        OnResize(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
        return false;
    }

} // namespace fenix
