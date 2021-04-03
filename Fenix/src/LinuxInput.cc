#include "Fenix/Core/Input.hh"

#include "Fenix/Core/Application.hh"
#include "GLFW/glfw3.h"

namespace Fenix {

    bool Input::IsKeyPressed(KeyCode keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(const MouseCode button)
    {
        auto* window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition()
    {
        auto* window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
        double x_pos, y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);

        return { static_cast<float>(x_pos), static_cast<float>(y_pos) };
    }

    float Input::GetMouseX()
    {
        return GetMousePosition().x;
    }

    float Input::GetMouseY()
    {
        return GetMousePosition().y;
    }

} // namespace Fenix
