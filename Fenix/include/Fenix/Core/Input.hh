#pragma once

#include <glm/vec2.hpp>

#include "KeyCodes.hh"
#include "MouseCodes.hh"

namespace Fenix {

    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);

        static bool IsMouseButtonPressed(MouseCode button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };

} // namespace Fenix
