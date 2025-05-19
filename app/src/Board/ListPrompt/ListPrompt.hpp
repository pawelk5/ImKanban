#pragma once
#include "pch.h"
#include "List.hpp"
#include "Core/PromptBase/InputPrompt.hpp"

struct ListPromptContext {
    int listIndex = -1;
};

/// Prompt for adding new or editing a list
class ListPrompt : public InputPrompt<ListData, ListPromptContext> {
public:
    ListPrompt();
    
private:
    void DrawImpl(sf::RenderTarget& target) override;
    void OpenImpl() override;
    const char* GetPopupID() override;
};