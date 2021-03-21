#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Fenix {

    /// @class OrthographicCamera
    ///
    /// An abstract camera class that calculates the corresponding View and Projection
    /// matrices and keeps track of its position and rotation. Note that a camera by
    /// itself shouldn't be responsible of treating input, that's the responibility of
    /// the camera controller.
    class OrthographicCamera
    {
    public:
        /// Constructor with scalar values, near and far planes default to -1.0 and 1.0
        /// respectively.
        OrthographicCamera(float left, float right, float bottom, float top);
        void SetProjection(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
        void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

        const glm::mat4& GetProjViewMatrix() const { return m_ProjViewMatrix; }
    private:
        void RecalculateViewMatrix();
    private:
        // Matrices
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjViewMatrix;
        // Attributes
        glm::vec3 m_Position;
        float m_Rotation = 0.0f;
    };

}
