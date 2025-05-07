#pragma once
#include "ListPrompt/ListPrompt.hpp"
#include "CardPrompt/CardPrompt.hpp"
#include "Core/View/ViewBase.hpp"
#include "Board.hpp"

class BoardView : public ViewBase {
private:
    using CardDragDropPayload = Board::MoveData;
    using Callback = std::function<void()>;

public:
    using BoardPointer = std::shared_ptr<Board>;

public:
    BoardView(const BoardPointer& pointer);

    void Draw(sf::RenderTarget& target) override;
    void Update(float deltaTime) override;
    void EventUpdate(const sf::Event& event) override;

private:
    BoardPointer m_board;
    ListPrompt m_listPrompt;
    CardPrompt m_cardPrompt;

    ImVec2 m_listSize;
    
private:
    
    void DrawAllLists();
    void DrawAllCards(Board::ElementArrayIterator iter);

    void DrawList(Board::ElementArrayIterator iter, const Callback& deleteCallback, const Callback& openPromptCallback);
    void DrawCard(Card& card, const Callback& deleteCallback, const Callback& openPromptCallback,
        const Board::ItemIndex& itemIndex);

    void DrawListPrompt();
    void DrawCardPrompt();

// "event handlers"
private:
    struct CardDragDropData {
        CardDragDropPayload source;
        CardDragDropPayload destination;
    };

    std::optional<CardDragDropData> m_dragdropData;

    void CreateCardDragDropSource(const Card& card, const CardDragDropPayload& payload);
    void CreateCardDragDropTarget(const CardDragDropPayload& destination);

    void DragDropUpdate();

private:
    struct OpenPromptData {
        Board::ItemIndex index;

        std::variant<std::optional<ListData>, std::optional<Card::Data>> promptData;
    };
    std::optional<OpenPromptData> m_openPromptData;

    void OpenPromptUpdate();
    void OpenCardPrompt(int listIndex, int cardIndex, const std::optional<Card::Data>& data);
    void OpenListPrompt(int listIndex, const std::optional<ListData>& data);

private:
    struct DeleteItemData {
        Board::ItemIndex index;
    };
    
    std::optional<DeleteItemData> m_deleteItemData;
    void DeleteItemUpdate();
    void DeleteItem(const DeleteItemData& data);
};