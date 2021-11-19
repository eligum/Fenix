#pragma once

#include "fenix/core/window.hh"
#include "fenix/renderer/graphics_context.hh"

#include <GLFW/glfw3.h>

namespace fenix {

    class LinuxWindow : public Window
    {
    public:
        LinuxWindow(const WindowProps& props);
        ~LinuxWindow();

        void OnUpdate() override;

        uint32_t GetWidth() const override { return m_Data.Width; }
        uint32_t GetHeight() const override { return m_Data.Height; }

        // Window attributes
        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void* GetNativeWindow() const override { return m_Window; }
    private:
        void Init(const WindowProps& props);
        void Shutdown();
    private:
        GLFWwindow* m_Window;
        GraphicsContext* m_Context;

        struct WindowData
        {
            std::string Title;
            uint32_t Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };

} // namespace fenix
