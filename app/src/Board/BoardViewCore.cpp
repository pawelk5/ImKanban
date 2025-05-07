#include "pch.h"
#include "Core/EventHandler/EventHandler.hpp"
#include "BoardView.hpp"


BoardView::BoardView(const BoardView::BoardPointer &pointer)
    : m_board(pointer)
{
    m_listSize = {250.f, 0.f};

    SetUpEventHandlers();    
}

void BoardView::Update(float deltaTime) { 
    m_dragdropHandler.Update();
    m_openPromptHandler.Update();
    m_deleteItemHandler.Update();
}

void BoardView::EventUpdate(const sf::Event &event) { ; }

void BoardView::SetUpEventHandlers() {
    const auto& dragdropCallback = [this] (CardDragDropData m_data) {
        m_board->MoveCard( m_data.source, m_data.destination );
    };
    
    const auto& openPromptCallback = [this] (OpenPromptData data) {
        const auto& listIndex = data.index.list;
        const auto& cardIndex = data.index.card;
        if (std::holds_alternative<std::optional<ListData>>(data.promptData))
            m_listPrompt.Open(std::get<std::optional<ListData>>(data.promptData),
            { listIndex });
        else
            m_cardPrompt.Open(std::get<std::optional<Card::Data>>(data.promptData),
            { listIndex, cardIndex });
    };

    const auto& deleteItemCallback = [this] (DeleteItemData data) {
        const auto& listIndex = data.index.list;
        const auto& cardIndex = data.index.card;

        if (cardIndex == -1)
            m_board->RemoveElement(listIndex);
        else
            m_board->At(listIndex)->RemoveElement(cardIndex);
    };

    m_dragdropHandler = EventHandler<CardDragDropData>(dragdropCallback);
    m_openPromptHandler = EventHandler<OpenPromptData>(openPromptCallback);
    m_deleteItemHandler = EventHandler<DeleteItemData>(deleteItemCallback);
}


