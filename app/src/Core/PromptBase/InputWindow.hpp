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
    void Draw() override
    {
        if (!this->IsOpen())
            return;

        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 300, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(300, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

        if (ImGui::Begin(this->GetPopupID(), nullptr, defs::UIFlags::windowFlags))
        {
            this->DrawImpl();
            ImGui::Spacing();

            if (ImGui::Button(defs::Labels::okButtonLabel))
            {
                this->m_onExit(this->m_data, this->m_contextData);
                this->ClosePopup();
            }

            ImGui::SameLine();
            if (ImGui::Button(defs::Labels::cancelButtonLabel))
                this->ClosePopup();
        }
        ImGui::End();
    }

protected:
    /// Called in Draw function, for displaying widgets
    virtual void DrawImpl() = 0;
};