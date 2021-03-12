#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW         = -90.0f;
const float PITCH       = 0.0f;
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;

/**
 * @class An abstract camera class that processes input and calculates the
 * corresponding Euler Angles, Vectors and Matrices for use in OpenGL
 */
class Camera
{
public:
    // Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Angles
    float Yaw;
    float Pitch;
    // Options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

public:
    /**
     * Constructor with vectors.
     */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW,
           float pitch = PITCH);

    /**
     * Constructor with scalar values.
     */
    Camera(float posX, float posY, float posZ,
           float upX, float upY, float upZ,
           float yaw,
           float pitch);

    /**
     * @return The view matrix calculated using Euler Angles and the LookAt Matrix
     */
    glm::mat4 GetViewMatrix() const;

    /**
     * Processes input received from any keyboard-like input system. Accepts input
     * parameter in the form of camera defined ENUM (to abstract it from windowing
     * systems).
     */
    void ProcessAction(CameraMovement direction, float deltaTime);

    /**
     * Processes input received from a mouse input system. Expects the offset value
     * in both the x and y direction.
     */
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

    /**
     * Processes input received from a mouse scroll-wheel event. Only requires input
     * on the vertical wheel-axis
     */
    void ProcessMouseScroll(float scrollOffset);

private:
    /**
     * Calculates the front vector from the Camera's (updated) Euler Angles
     */
    void updateCameraVectors();
};

#endif
