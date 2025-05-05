#pragma once
#include "pch.h"
#include "Card.hpp"
#include "PromptBase/InputPrompt.hpp"

// TODO: Change to something not prone to off-by-one errors
struct CardPromptContext {
    int listIndex = -1;
    int cardIndex = -1;
};

class CardPrompt : public InputPrompt<Card::Data, CardPromptContext> {
public:
    CardPrompt();

private:
    void DrawImpl() override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};