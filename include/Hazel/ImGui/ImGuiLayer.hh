#pragma once

#include "Hazel/Core/Layer.hh"
#include "Hazel/Events/MouseEvent.hh"
#include "Hazel/Events/ApplicationEvent.hh"
#include "Hazel/Events/KeyEvent.hh"

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
