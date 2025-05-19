#pragma once
#include "Core/Utils/Constants.hpp"
#include "PromptBase.hpp"

/// Base class for input prompts (forms)
///
/// Calls onExit callback when user confirms changes (presses OK button)
template <typename InputData, typename ContextData>
class InputPrompt : public PromptBase<InputData, ContextData> {
public:
    virtual ~InputPrompt() = default;
    
    /// Override of Draw function
    /// Draws a modal popup with OK and Close buttons
    void Draw(sf::RenderTarget& target) override {
        if (!this->IsOpen())
            return;

        ImGui::OpenPopup(this->GetPopupID());

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2{0.5f, 0.5f});

        if (ImGui::BeginPopupModal(this->GetPopupID(), nullptr, UIFlags::promptFlags)) {
            this->DrawImpl(target);
            ImGui::Spacing();
            
            if (ImGui::Button(Labels::okButtonLabel)){
                this->m_onExit(this->m_data, this->m_contextData);
                this->ClosePopup();
            }
        
            ImGui::SameLine();
            if (ImGui::Button(Labels::cancelButtonLabel))
                this->ClosePopup();
        }
        ImGui::EndPopup();
    }
protected:
    /// Called in Draw function, for displaying widgets
    virtual void DrawImpl(sf::RenderTarget& target) = 0;
};