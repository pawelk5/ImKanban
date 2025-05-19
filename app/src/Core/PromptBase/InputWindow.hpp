#pragma once
#include "Core/Utils/Constants.hpp"
#include "PromptBase.hpp"

/// Base class for input windows (forms)
///
/// Calls onExit callback when user confirms changes (presses OK button)
template <typename InputData, typename ContextData>
class InputWindow : public PromptBase<InputData, ContextData>
{
public:
    /// Override of Draw function
    /// Draws a left-side window with OK and Close buttons
    void Draw(sf::RenderTarget &target) override
    {
        if (!this->IsOpen())
            return;

        const int width = 500;
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - width, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

        if (ImGui::Begin(this->GetPopupID(), nullptr, UIFlags::windowFlags))
        {
            this->DrawImpl(target);
            ImGui::Spacing();

            if (ImGui::Button(Labels::okButtonLabel))
            {
                this->m_onExit(this->m_data, this->m_contextData);
                this->ClosePopup();
            }

            ImGui::SameLine();
            if (ImGui::Button(Labels::cancelButtonLabel))
                this->ClosePopup();
        }
        ImGui::End();
    }

protected:
    /// Called in Draw function, for displaying widgets
    virtual void DrawImpl(sf::RenderTarget &target) = 0;
};