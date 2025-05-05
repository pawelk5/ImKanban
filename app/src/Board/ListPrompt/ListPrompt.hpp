#pragma once
#include "pch.h"
#include "List.hpp"
#include "Board/PromptBase/PromptBase.hpp"

class ListPrompt : public PromptBase<List::Data, uint32_t> {
public:
    ListPrompt();
    
private:
    void DrawImpl() override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};