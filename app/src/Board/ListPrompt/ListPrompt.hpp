#pragma once
#include "pch.h"
#include "List.hpp"
#include "Core/PromptBase/InputPrompt.hpp"

struct ListPromptContext {
    int listIndex = -1;
};

class ListPrompt : public InputPrompt<ListData, ListPromptContext> {
public:
    ListPrompt();
    
private:
    void DrawImpl() override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};