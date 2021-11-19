#pragma once

#include "fenix/core/layer.hh"
#include "fenix/events/mouse_event.hh"
#include "fenix/events/application_event.hh"
#include "fenix/events/key_event.hh"

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
