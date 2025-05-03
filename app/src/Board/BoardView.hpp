#pragma once
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

private:
    void DrawList(List& list, const ImVec2& listSize);
    void DrawCard(Card& card);
};