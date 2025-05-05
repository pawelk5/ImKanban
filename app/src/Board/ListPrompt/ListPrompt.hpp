#pragma once
#include "pch.h"
#include "List.hpp"
#include "PromptBase/InputPrompt.hpp"

// TODO: Change to something not prone to off-by-one errors
struct ListPromptContext {
    int listIndex = -1;
};

class ListPrompt : public InputPrompt<List::Data, ListPromptContext> {
public:
    ListPrompt();
    
private:
    void DrawImpl() override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};