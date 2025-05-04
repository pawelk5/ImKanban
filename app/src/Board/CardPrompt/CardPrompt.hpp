#pragma once
#include "Card.hpp"

class CardPrompt {
public:
    CardPrompt();

    void Draw(const std::function<void(const Card&)>& onSubmit);

    void Open(uint32_t index);
    bool IsOpen();
    
    uint32_t GetIndex();
private:
    bool m_open;
    uint32_t m_index;

    struct CardData {
        std::string title;
    } m_cardData;
    
private:
    void ClosePopup();
};