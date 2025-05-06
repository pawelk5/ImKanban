#pragma once
#include "ListPrompt/ListPrompt.hpp"
#include "CardPrompt/CardPrompt.hpp"
#include "View/ViewBase.hpp"
#include "Board.hpp"

class BoardView : public ViewBase {
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
    using DeleteCallback = std::function<void()>;
    void DrawList(List& list, const DeleteCallback& callback, const ListPromptContext& promptContext);
    void DrawCard(Card& card, const DeleteCallback& callback, const CardPromptContext& promptContext);

    void DrawListPrompt();
    void DrawCardPrompt();

private:
    // these structs have the same fields (FOR NOW)
    using CardDragDropPayload = CardPromptContext;

    struct CardDragDropData {
        CardDragDropPayload source;
        CardDragDropPayload destination;
    };

    std::optional<CardDragDropData> m_dragdropData;

    void CreateCardDragDropSource(const Card& card, const CardDragDropPayload& payload);
    void CreateCardDragDropTarget(const CardDragDropPayload& destination);

    void DragDropUpdate();
};