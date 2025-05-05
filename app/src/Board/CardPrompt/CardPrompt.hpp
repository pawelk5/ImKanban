#pragma once
#include "pch.h"
#include "Card.hpp"
#include "Board/PromptBase/PromptBase.hpp"

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