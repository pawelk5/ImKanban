#pragma once
#include "pch.h"
#include "Board.hpp"
#include "PromptBase/InputPrompt.hpp"


class CardPrompt : public InputPrompt<Card::Data, Board::ItemIndex> {
public:
    CardPrompt();

private:
    void DrawImpl() override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};