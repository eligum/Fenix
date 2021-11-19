#pragma once

#include "fenix/renderer/camera.hh"

namespace fenix {

    class SceneCamera : public Camera
    {
    public:
        SceneCamera();
        ~SceneCamera() = default;

        void SetOrthographic(float size, float z_near, float z_far);
        void SetViewportSize(uint32_t width, uint32_t height);
    private:
        void RecalculateProjection();
    private:
        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f;
        float m_OrthographicFar = 1.0f;
        float m_AspectRatio = 1.0f;
    };

} // namespace fenix
