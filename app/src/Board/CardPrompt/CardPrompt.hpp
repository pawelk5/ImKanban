#pragma once
#include "pch.h"
#include "Card.hpp"
#include "Board/PromptBase/PromptBase.hpp"

// TODO: Change to something not prone to off-by-one errors
struct CardPromptData {
    int listIndex = -1;
    int cardIndex = -1;
};

class CardPrompt : public PromptBase<Card::Data, CardPromptData> {
public:
    CardPrompt();

private:
    void DrawImpl() override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};