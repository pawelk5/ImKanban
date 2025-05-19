#pragma once
#include "Core/Utils/Constants.hpp"
#include "Core/PromptBase/PromptBase.hpp"

/// Base class confirming actions
///
/// Calls onExit callback when user confirms changes (presses OK button)
/// Uses char as a template just to satisfy compiler requirements
template <typename ContextData>
class ConfirmPrompt : public PromptBase<char, ContextData> {
public:
    virtual ~ConfirmPrompt() = default;

    /// Override of Draw function
    /// Draws a modal popup with OK and Close buttons
    void Draw(sf::RenderTarget& target) override {
        if (!this->IsOpen())
            return;

        ImGui::OpenPopup(this->GetPopupID());

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2{0.5f, 0.5f});

        if (ImGui::BeginPopupModal(this->GetPopupID(), nullptr, UIFlags::promptFlags)) {
            ImGui::Text("%s", this->GetPromptMessage());
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

    /// Override open function
    void OpenImpl() override { ; }
    
protected:
    /// Override id (header) of the modal prompt
    const char* GetPopupID() override {
        return Labels::confirmPromptLabel;
    }

    /// Returns prompt message
    virtual const char* GetPromptMessage() = 0;
};