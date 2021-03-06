#pragma once

#include "Layer.hh"

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
        float m_Time = 0.0f;
    };

} // namespace flyCore
