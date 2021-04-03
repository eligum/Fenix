#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Fenix {

    /// @class OrthographicCamera
    ///
    /// A top-down view camera class that calculates the corresponding View and Projection
    /// matrices and keeps track of its position and rotation. Note that this camera does
    /// not treat input by itself, that responsibility is passed to the camera controller.
    class OrthographicCamera
    {
    public:
        /// Constructor with scalar values, near and far planes default to -1.0 and 1.0
        /// respectively.
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
        float GetRotation() const { return m_Rotation; }
        void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetProjViewMatrix() const { return m_ProjViewMatrix; }
    private:
        void RecalculateViewMatrix();
    private:
        // Matrices
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjViewMatrix;
        // Attributes
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Rotation = 0.0f;
    };

}
