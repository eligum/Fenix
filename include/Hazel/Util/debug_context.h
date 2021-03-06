#ifndef DEBUG_CONTEXT_H
#define DEBUG_CONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Callback function for OpenGL debug output.
void glDebugOutputCB(GLenum source, GLenum type, uint32_t id, GLenum severity,
                     GLsizei length, const char* message, const void* user_param);

#endif
