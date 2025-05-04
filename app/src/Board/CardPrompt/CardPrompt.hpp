#pragma once
#include "pch.h"
#include "Card.hpp"

class CardPrompt {
public:
    CardPrompt();

    void Draw(const std::function<void(const Card::Data&)>& onSubmit);

    void Open(const std::optional<Card::Data>& data, uint32_t index);
    bool IsOpen();
    
    uint32_t GetIndex();
private:
    bool m_open;
    uint32_t m_index;

    Card::Data m_data;

private:
    void ClosePopup();
};