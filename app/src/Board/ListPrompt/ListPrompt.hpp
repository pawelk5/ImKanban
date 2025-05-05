#pragma once
#include "pch.h"
#include "List.hpp"
#include "Board/PromptBase/PromptBase.hpp"

struct ListPromptData {
    int listIndex = -1;
};

class ListPrompt : public PromptBase<List::Data, ListPromptData> {
public:
    ListPrompt();
    
private:
    void DrawImpl() override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};