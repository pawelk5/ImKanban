#pragma once
#include "Core/Utils/Constants.hpp"
#include "PromptBase.hpp"

/// Base class for input prompts (forms)
///
/// Calls onExit callback when user confirms changes (presses OK button)
template <typename InputData, typename ContextData>
class InputPrompt : public PromptBase<InputData, ContextData> {
public:
    /// Override of Draw function
    /// Draws a modal popup with OK and Close buttons
    void Draw() override {
        if (!this->IsOpen())
            return;

        ImGui::OpenPopup(this->GetPopupID());

        if (ImGui::BeginPopupModal(this->GetPopupID(), nullptr, defs::UIFlags::promptFlags)) {
            this->DrawImpl();
            ImGui::Spacing();
            
            if (ImGui::Button(defs::Labels::okButtonLabel)){
                this->m_onExit(this->m_data, this->m_contextData);
                this->ClosePopup();
            }
        
            ImGui::SameLine();
            if (ImGui::Button(defs::Labels::cancelButtonLabel))
                this->ClosePopup();
        }
        ImGui::EndPopup();
    }
protected:
    /// Called in Draw function, for displaying widgets
    virtual void DrawImpl() = 0;
};