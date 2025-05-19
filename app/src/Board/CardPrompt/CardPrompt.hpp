#pragma once
#include "pch.h"
#include "Board.hpp"
#include "Core/PromptBase/InputWindow.hpp"

/// Prompt for adding new or editing a card
class CardPrompt : public InputWindow<CardData, Board::ItemIndex>
{
public:
    CardPrompt();

private:
    void DrawImpl(sf::RenderTarget& target) override;
    void OpenImpl() override;
    const char *GetPopupID() override;
};