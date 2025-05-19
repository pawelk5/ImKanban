#pragma once

#include <string>
#include <imgui.h>
#include <Card.hpp>
#include "Core/PromptBase/PromptBase.hpp"
#include "Board.hpp"

/// Side view card for displaying and editing card details
///
/// This class uses PromptBase as a base and customizes it for a side view card

struct FullCardViewData
{
    Card *selectedCard;
};

class FullCardView : public PromptBase<FullCardViewData, Board::ItemIndex>
{
public:
    /// Constructs a new FullCardView
    // FullCardView(); //= default;
    FullCardView(std::function<void(Board::ItemIndex, std::optional<SubtaskData>)> m_open_subtask_prompt);

    /// Draws the side view card
    void Draw() override
    {
        if (!m_open)
            return;

        const int width = 500;
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - width, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
        // Begin the ImGui window
        if (ImGui::Begin(GetPopupID(), &m_open, ImGuiWindowFlags_AlwaysAutoResize))
        {
            // Input field for card details
            // ImGui::InputText("Card Details", &m_data);
            this->DrawImpl();

            // Cancel button
            if (ImGui::Button("Close"))
            {
                ClosePopup();
            }
        }
        ImGui::End();
    }

protected:
    std::function<void(Board::ItemIndex, std::optional<SubtaskData>)> m_open_subtask_prompt;
    /// Handles data initialization when the side view card is opened
    void OpenImpl() override
    {
        // Custom initialization logic (if needed)
    }

    void DrawImpl();

    /// Returns the ImGui ID of the popup
    const char *GetPopupID() override
    {
        return "FullCardView";
    }
};