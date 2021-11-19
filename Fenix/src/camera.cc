#include "fenix/renderer/camera.hh"

namespace fenix {

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
    {
        m_ProjViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ProjViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, m_Position);
        transform = glm::rotate(transform, glm::radians(m_Rotation), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ProjViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

}
