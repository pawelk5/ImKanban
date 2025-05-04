#pragma once
#include "pch.h"
#include "List.hpp"

class ListPrompt {
public:
    ListPrompt();

    void Draw(const std::function<void(const List&)>& onSubmit);

    void Open();
    bool IsOpen();
    
private:
    bool m_open;

private:
    struct ListData {
        std::string name;
    } m_listData;

    void ClosePopup();
};