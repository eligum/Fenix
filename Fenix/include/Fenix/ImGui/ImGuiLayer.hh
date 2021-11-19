#pragma once

#include "Fenix/Core/Layer.hh"
#include "Fenix/Events/MouseEvent.hh"
#include "Fenix/Events/ApplicationEvent.hh"
#include "Fenix/Events/KeyEvent.hh"

namespace fenix {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(Event& event) override;

        void Begin();
        void End();

        void BlockEvents(bool block) { m_BlockEvents = block; }
    private:
        bool m_BlockEvents = true;
    };

} // namespace fenix
