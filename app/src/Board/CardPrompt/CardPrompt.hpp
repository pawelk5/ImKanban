#pragma once
#include "pch.h"
#include "Card.hpp"
#include "Board/PromptBase/PromptBase.hpp"

class CardPrompt : public PromptBase<Card::Data, uint32_t> {
public:
    CardPrompt();
    
private:
    void DrawImpl() override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};