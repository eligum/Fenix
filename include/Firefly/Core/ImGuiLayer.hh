#pragma once

#include "Layer.hh"
#include "Events/MouseEvent.hh"
#include "Events/ApplicationEvent.hh"
#include "Events/KeyEvent.hh"

namespace flyCore {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& evt);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& evt);
        bool OnMouseMovedEvent(MouseMovedEvent& evt);
        bool OnMouseScrolledEvent(MouseScrolledEvent& evt);
        bool OnKeyPressedEvent(KeyPressedEvent& evt);
        bool OnKeyReleasedEvent(KeyReleasedEvent& evt);
        bool OnKeyTypedEvent(KeyTypedEvent& evt);
        bool OnWindowResizedEvent(WindowResizeEvent& evt);
    private:
        float m_Time = 0.0f;
    };

} // namespace flyCore
