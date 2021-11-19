#pragma once

#include <glm/vec2.hpp>

#include "key_codes.hh"
#include "mouse_codes.hh"

namespace fenix {

    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);

        static bool IsMouseButtonPressed(MouseCode button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };

} // namespace fenix
