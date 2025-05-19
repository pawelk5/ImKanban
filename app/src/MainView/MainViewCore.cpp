#include "pch.h"
#include "Core/EventHandler/EventHandler.hpp"
#include "MainView.hpp"


MainView::MainView(std::shared_ptr<BoardList> boardList) 
    : m_viewNavigation(std::nullopt), m_boardList(boardList)
{
    const auto boardPromptCallback = 
    [this](const BoardData& data, const BoardPromptContext& promptContext) {
        m_boardList->AddElement(data);
        m_viewNavigation = OpenBoardView{ std::make_shared<Board>( data ) };
    };

    m_boardPrompt.SetOnExitCallback(boardPromptCallback);
}

void MainView::Update(float deltaTime) {
    ;
}

void MainView::EventUpdate(const sf::Event &event) { 
    m_boardPrompt.EventUpdate(event);
}

ViewNavigation MainView::GetState() {
    return m_viewNavigation;
}