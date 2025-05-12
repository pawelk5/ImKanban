#include "pch.h"
#include "Core/EventHandler/EventHandler.hpp"
#include "BoardView.hpp"


BoardView::BoardView(const BoardView::BoardPointer &pointer)
    : m_board(pointer)
{
    m_listSize = {250.f, 0.f};

    SetUpEventHandlers();
    SetUpPromptCallbacks(); 
}

void BoardView::Update(float deltaTime) {
    m_dragdropHandler.Update();
    m_openPromptHandler.Update();
    m_deleteItemHandler.Update();
}

void BoardView::EventUpdate(const sf::Event &event) { 
    m_cardPrompt.EventUpdate(event);
    m_listPrompt.EventUpdate(event);
    m_deleteItemPrompt.EventUpdate(event);
}

void BoardView::SetUpEventHandlers() {
    /// DRAG AND DROP CALLBACK
    const auto& dragdropCallback = [this] (DragDropData m_data) {
        if (m_data.source.card != -1)
            m_board->MoveCard( m_data.source, m_data.destination );
        else
            m_board->MoveList( m_data.source.list, m_data.destination.list );
    };
    
    /// OPEN PROMPT CALLBACK
    const auto& openPromptCallback = [this] (OpenPromptData data) {
        const auto& listIndex = data.index.list;
        const auto& cardIndex = data.index.card;
        const auto& promptData = data.promptData;
        if (std::holds_alternative<std::optional<ListData>>(promptData))
            m_listPrompt.Open(std::get<std::optional<ListData>>(promptData),
            { listIndex });
        else
            m_cardPrompt.Open(std::get<std::optional<CardData>>(promptData),
            { listIndex, cardIndex });
    };


    /// DELETE CALLBACK
    const auto& deleteItemCallback = [this] (DeleteItemData data) {
        m_deleteItemPrompt.Open(std::nullopt, data.index);
    };

    m_dragdropHandler = EventHandler<DragDropData>(dragdropCallback);
    m_openPromptHandler = EventHandler<OpenPromptData>(openPromptCallback);
    m_deleteItemHandler = EventHandler<DeleteItemData>(deleteItemCallback);
}

void BoardView::SetUpPromptCallbacks() {
    /// LIST PROMPT CALLBACK
    const auto listPromptSubmitCallback = 
    [this](const ListData &listData, const ListPromptContext& promptContext)
    {
        if (promptContext.listIndex < 0)
            m_board->AddElement(List(listData));
        else
            m_board->At(promptContext.listIndex)->Update(listData);
    };


    /// CARD PROMPT CALLBACK
    const auto cardPromptSubmitCallback =
        [this](const CardData &cardData, const Board::ItemIndex& promptContext)
    {
        auto &list = m_board->At(promptContext.list);
        if (promptContext.card < 0)
            list->AddElement(Card(cardData));
        else
            list->At(promptContext.card)->Update(cardData);
    };

    /// DELETE ITEM PROMPT
    const auto deleteItemPromptCallback =
        [this](int, const Board::ItemIndex& itemIndex)
    {
        const auto& listIndex = itemIndex.list;
        const auto& cardIndex = itemIndex.card;

        if (cardIndex == -1)
            m_board->RemoveElement(listIndex);
        else
            m_board->At(listIndex)->RemoveElement(cardIndex);
    };

    m_listPrompt.SetOnExitCallback(listPromptSubmitCallback);
    m_cardPrompt.SetOnExitCallback(cardPromptSubmitCallback);
    m_deleteItemPrompt.SetOnExitCallback(deleteItemPromptCallback);
}

