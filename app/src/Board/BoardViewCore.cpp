#include "pch.h"
#include "Core/EventHandler/EventHandler.hpp"
#include "BoardView.hpp"

BoardView::BoardView(const BoardView::BoardPointer &pointer)
    : m_board(pointer), m_fullCardView(
                            [this](Board::ItemIndex itemIndex,
                                   std::optional<SubtaskData> SubtaskData)
                            { m_openPromptHandler.Trigger(
                                  OpenPromptData{itemIndex, SubtaskData}); })
{
    m_listSize = {250.f, 0.f};

    SetUpEventHandlers();
    SetUpPromptCallbacks();
}

void BoardView::Update(float deltaTime)
{
    m_dragdropHandler.Update();
    m_openPromptHandler.Update();
    m_deleteItemHandler.Update();
}

void BoardView::EventUpdate(const sf::Event &event)
{
    m_cardPrompt.EventUpdate(event);
    m_listPrompt.EventUpdate(event);
    m_subtaskPrompt.EventUpdate(event);
    m_fullCardView.EventUpdate(event);
}

void BoardView::SetUpEventHandlers()
{
    /// DRAG AND DROP CALLBACK
    const auto &dragdropCallback = [this](DragDropData m_data)
    {
        if (m_data.source.card != -1)
            m_board->MoveCard(m_data.source, m_data.destination);
        else
            m_board->MoveList(m_data.source.list, m_data.destination.list);
    };

    /// OPEN PROMPT CALLBACK
    const auto &openPromptCallback = [this](OpenPromptData data)
    {
        const auto &listIndex = data.index.list;
        const auto &cardIndex = data.index.card;
        const auto &subtaskIndex = data.index.subtask;
        const auto &promptData = data.promptData;
        if (std::holds_alternative<std::optional<ListData>>(promptData))
            m_listPrompt.Open(std::get<std::optional<ListData>>(promptData),
                              {listIndex});
        else if (std::holds_alternative<std::optional<CardData>>(promptData))
            m_cardPrompt.Open(std::get<std::optional<CardData>>(promptData),
                              {listIndex,
                               cardIndex});
        else if (std::holds_alternative<std::optional<SubtaskData>>(promptData))
            m_subtaskPrompt.Open(std::get<std::optional<SubtaskData>>(promptData),
                                 {
                                     listIndex,
                                     cardIndex,
                                     subtaskIndex,
                                 });
        else if (std::holds_alternative<std::optional<FullCardViewData>>(promptData))
            m_fullCardView.Open(std::get<std::optional<FullCardViewData>>(promptData),
                                {listIndex,
                                 cardIndex});
        else
            throw std::runtime_error("Invalid prompt data");
    };

    /// DELETE CALLBACK
    const auto &deleteItemCallback = [this](DeleteItemData data)
    {
        const auto &listIndex = data.index.list;
        const auto &cardIndex = data.index.card;
        const auto &subtaskIndex = data.index.subtask;

        if (cardIndex == -1)
            m_board->RemoveElement(listIndex);
        else
            m_board->At(listIndex)->RemoveElement(cardIndex);
    };

    m_dragdropHandler = EventHandler<DragDropData>(dragdropCallback);
    m_openPromptHandler = EventHandler<OpenPromptData>(openPromptCallback);
    m_deleteItemHandler = EventHandler<DeleteItemData>(deleteItemCallback);
}

void BoardView::SetUpPromptCallbacks()
{
    /// LIST PROMPT CALLBACK
    const auto listPromptSubmitCallback =
        [this](const ListData &listData, const ListPromptContext &promptContext)
    {
        if (promptContext.listIndex < 0)
            m_board->AddElement(List(listData));
        else
            m_board->At(promptContext.listIndex)->Update(listData);
    };

    /// CARD PROMPT CALLBACK
    const auto cardPromptSubmitCallback =
        [this](const CardData &cardData, const Board::ItemIndex &promptContext)
    {
        auto &list = m_board->At(promptContext.list);
        if (promptContext.card < 0)
            list->AddElement(Card(cardData));
        else
            list->At(promptContext.card)->Update(cardData);
    };

    /// SUBTASK PROMPT CALLBACK
    const auto subtaskPromptSubmitCallback =
        [this](const SubtaskData &subtaskData, const Board::ItemIndex &promptContext)
    {
        auto &list = m_board->At(promptContext.list);
        auto card = list->At(promptContext.card);

        if (promptContext.subtask < 0)
            card->AddElement(Subtask(subtaskData));
        else
        {
            auto subtask = card->At(promptContext.subtask);
            subtask->SetTitle(subtaskData.title);
            subtask->SetCompleted(subtaskData.isCompleted);
        }
    };

    m_listPrompt.SetOnExitCallback(listPromptSubmitCallback);
    m_cardPrompt.SetOnExitCallback(cardPromptSubmitCallback);
    m_subtaskPrompt.SetOnExitCallback(subtaskPromptSubmitCallback);
}
