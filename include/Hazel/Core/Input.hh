#pragma once

#include <glm/glm.hpp>

#include "KeyCodes.hh"
#include "MouseCodes.hh"

namespace Hazel {

    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);

        static bool IsMouseButtonPressed(MouseCode button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };

} // namespace Hazel
