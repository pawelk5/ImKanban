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

private:
    void DrawList(List& list, const ImVec2& listSize, uint32_t index);
    void DrawCard(Card& card, uint32_t index);
};