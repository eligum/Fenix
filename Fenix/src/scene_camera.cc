#include "fenix/scene/scene_camera.hh"

#include <glm/gtc/matrix_transform.hpp>

namespace fenix {

    SceneCamera::SceneCamera()
    {
        RecalculateProjection();
    }

    void SceneCamera::SetOrthographic(float camera_size, float z_near, float z_far)
    {
        m_OrthographicSize = camera_size;
        m_OrthographicNear = z_near;
        m_OrthographicFar  = z_far;
        RecalculateProjection();
    }

    void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
    {
        m_AspectRatio = width / static_cast<float>(height);
        RecalculateProjection();
    }

    void SceneCamera::RecalculateProjection()
    {
        const float orthoLeft   = -m_OrthographicSize * m_AspectRatio * 0.5f;
        const float orthoRight  =  m_OrthographicSize * m_AspectRatio * 0.5f;
        const float orthoBottom = -m_OrthographicSize * 0.5f;
        const float orthoTop    =  m_OrthographicSize * 0.5f;

        m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
    }

} // namespace fenix
