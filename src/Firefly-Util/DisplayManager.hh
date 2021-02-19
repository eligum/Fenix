#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>

class DisplayManager
{
public:
    DisplayManager(int width, int height, const char* title);
    ~DisplayManager();
    void Set_background_color(uint8_t red, uint8_t green, uint8_t blue);
    int Get_FPS();
private:
    GLFWwindow* window;
    uint32_t screen_width;
    uint32_t screen_height;
    std::string title;
private:
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
