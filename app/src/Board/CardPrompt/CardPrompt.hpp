#pragma once
#include "pch.h"
#include "Board.hpp"
#include "Core/PromptBase/InputPrompt.hpp"

/// Prompt for adding new or editing a card
class CardPrompt : public InputPrompt<CardData, Board::ItemIndex> {
public:
    CardPrompt();

private:
    void DrawImpl() override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};