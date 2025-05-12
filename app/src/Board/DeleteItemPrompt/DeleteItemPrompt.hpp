#include "pch.h"
#include "Board.hpp"
#include "Core/PromptBase/InputPrompt.hpp"
#include "Core/ConfirmPrompt/ConfirmPrompt.hpp"

/// Prompt for adding new or editing a card
class DeleteItemPrompt : public ConfirmPrompt<Board::ItemIndex> {
public:
    DeleteItemPrompt();

private:
    const char* GetPromptMessage() override;
};