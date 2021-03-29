#pragma once

#include "Fenix/Core/Layer.hh"
#include "Fenix/Events/MouseEvent.hh"
#include "Fenix/Events/ApplicationEvent.hh"
#include "Fenix/Events/KeyEvent.hh"

namespace Fenix {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };

} // namespace Fenix
