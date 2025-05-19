#pragma once
#include "pch.h"
#include "Core/PromptBase/InputWindow.hpp"
#include "Subtask.hpp"
#include "Board.hpp"

/// Prompt for adding or editing a subtask
class SubtaskPrompt : public InputWindow<SubtaskData, Board::ItemIndex>
{
public:
    SubtaskPrompt();

private:
    void DrawImpl(sf::RenderTarget &target) override;
    void OpenImpl() override;
    const char *GetPopupID() override;
};
