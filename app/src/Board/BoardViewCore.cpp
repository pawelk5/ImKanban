#include "pch.h"
#include "BoardView.hpp"


BoardView::BoardView(const BoardView::BoardPointer &pointer)
    : m_board(pointer)
{
    m_dragdropData = std::nullopt;

    m_listSize = {250.f, 0.f};
}

void BoardView::Update(float deltaTime) { 
    DragDropUpdate();
    OpenPromptUpdate();
    DeleteItemUpdate();
}

void BoardView::EventUpdate(const sf::Event &event) { ; }

void BoardView::DragDropUpdate() {
    if (!m_dragdropData)
        return;

    m_board->MoveCard( m_dragdropData->source, m_dragdropData->destination );

    m_dragdropData = std::nullopt;
}

void BoardView::OpenPromptUpdate() {
    if (!m_openPromptData)
        return;
    
    const auto& listIndex = m_openPromptData->index.list;
    const auto& cardIndex = m_openPromptData->index.card;

    if (std::holds_alternative<std::optional<ListData>>(m_openPromptData->promptData))
        m_listPrompt.Open(std::get<std::optional<ListData>>(m_openPromptData->promptData),
            { listIndex });
    else
        m_cardPrompt.Open(std::get<std::optional<Card::Data>>(m_openPromptData->promptData),
        { listIndex, cardIndex });
    
    m_openPromptData = std::nullopt;
}

void BoardView::DeleteItemUpdate() {
    if (!m_deleteItemData)
        return;

    const auto& listIndex = m_deleteItemData->index.list;
    const auto& cardIndex = m_deleteItemData->index.card;

    if (cardIndex == -1)
        m_board->RemoveElement(listIndex);
    else
        m_board->At(listIndex)->RemoveElement(cardIndex);

    m_deleteItemData = std::nullopt;
}


void BoardView::OpenCardPrompt(int listIndex, int cardIndex, const std::optional<Card::Data>& data) {
    m_openPromptData = { listIndex, cardIndex, data };
}

void BoardView::OpenListPrompt(int listIndex, const std::optional<ListData>& data) {
    m_openPromptData = { listIndex, -1, data };
}

void BoardView::DeleteItem(const DeleteItemData& data) {
    m_deleteItemData = data;
}