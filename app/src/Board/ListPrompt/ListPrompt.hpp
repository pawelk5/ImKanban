#pragma once
#include "pch.h"
#include "List.hpp"

class ListPrompt {
public:
    ListPrompt();

    void Draw(const std::function<void(const List::Data&)>& onSubmit);

    void Open(const std::optional<List::Data>& data);
    bool IsOpen();
    
private:
    bool m_open;

private:
    List::Data m_data;

    void ClosePopup();
};