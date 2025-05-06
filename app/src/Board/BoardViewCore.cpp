#include "pch.h"
#include "BoardView.hpp"


BoardView::BoardView(const BoardView::BoardPointer &pointer)
    : m_board(pointer)
{
    auto &listRef = m_board->GetListsRef();
    m_dragdropData = std::nullopt;

    m_listSize = {250.f, 0.f};
}

void BoardView::Update(float deltaTime) { 
    DragDropUpdate();
}

void BoardView::EventUpdate(const sf::Event &event) { ; }

void BoardView::DragDropUpdate() {
    if (!m_dragdropData)
        return;

    const auto& source = m_dragdropData->source;
    const auto& dest = m_dragdropData->destination;
    auto& list = m_board->GetListsRef();
    m_board->MoveCard(
        list.begin() + source.listIndex,
        list.at(source.listIndex)->GetCardsRef().begin() + source.cardIndex,
        list.begin() + dest.listIndex,
        dest.cardIndex);

    m_dragdropData = std::nullopt;
}