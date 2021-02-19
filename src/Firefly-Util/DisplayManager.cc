#include <glad/glad.h>
#include "DisplayManager.hh"

DisplayManager::DisplayManager(int width, int height, const char* title)
    :
    screen_width(width),
    screen_height(height),
    title(title)
{
    window = glfwCreateWindow(screen_width, screen_height, title, nullptr, nullptr);
}

DisplayManager::~DisplayManager()
{
    glfwDestroyWindow(this->window);
}

void DisplayManager::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
