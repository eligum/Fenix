#pragma once

#include "Layer.hh"
#include "Events/MouseEvent.hh"
#include "Events/ApplicationEvent.hh"
#include "Events/KeyEvent.hh"

namespace Hazel {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void BeginDraw();
        void EndDraw();
    private:
        float m_Time = 0.0f;
    };

} // namespace Hazel
