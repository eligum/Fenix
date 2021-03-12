#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

    /// @class OrthographicCamera
    ///
    /// An abstract camera class that processes keyboard input and calculates the
    /// corresponding Euler Angles, Vectors and Matrices. Note that an orthographic
    /// camera does not respond to mouse input.
    class OrthographicCamera
    {
    public:
        /// Constructor with scalar values, near and far planes default to -1.0 and
        /// 1.0 respectively.
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
        void SetRotation(float rotatioin) { m_Rotation = rotatioin; RecalculateViewMatrix(); }

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
