#pragma once
#include "ListPrompt/ListPrompt.hpp"
#include "CardPrompt/CardPrompt.hpp"
#include "Core/View/ViewBase.hpp"
#include "Core/EventHandler/EventHandler.hpp"
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

// event handler data
private:
    struct CardDragDropData {
        CardDragDropPayload source;
        CardDragDropPayload destination;
    };

    struct OpenPromptData {
        Board::ItemIndex index;

        std::variant<std::optional<ListData>, std::optional<Card::Data>> promptData;
    };

    struct DeleteItemData {
        Board::ItemIndex index;
    };

// event handlers
private:
    EventHandler<CardDragDropData> m_dragdropHandler;
    EventHandler<OpenPromptData> m_openPromptHandler;
    EventHandler<DeleteItemData> m_deleteItemHandler;

private:
    void SetUpEventHandlers();

// drag and drop stuff
private:
    void CreateCardDragDropSource(const Card& card, const CardDragDropPayload& payload);
    void CreateCardDragDropTarget(const CardDragDropPayload& destination); 

};