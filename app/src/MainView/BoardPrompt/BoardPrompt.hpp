#pragma once
#include "Board.hpp"
#include "pch.h"
#include "List.hpp"
#include "Core/PromptBase/InputPrompt.hpp"

struct BoardPromptContext {
    int boardIndex = -1;
};

/// Prompt for adding new or editing a list
class BoardPrompt : public InputPrompt<BoardData, BoardPromptContext> {
public:
    BoardPrompt();
    
private:
    void DrawImpl(sf::RenderTarget& target) override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};