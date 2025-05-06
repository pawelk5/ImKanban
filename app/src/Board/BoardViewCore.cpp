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
}

void BoardView::EventUpdate(const sf::Event &event) { ; }

void BoardView::DragDropUpdate() {
    if (!m_dragdropData)
        return;

    m_board->MoveCard( m_dragdropData->source, m_dragdropData->destination );

    m_dragdropData = std::nullopt;
}