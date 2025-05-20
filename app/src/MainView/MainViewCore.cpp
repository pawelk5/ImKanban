#include "MainView/BoardPrompt/BoardPrompt.hpp"
#include "pch.h"
#include "Core/EventHandler/EventHandler.hpp"
#include "MainView.hpp"
#include <memory>


MainView::MainView(std::shared_ptr<BoardList> boardList) 
    : m_viewNavigation(std::nullopt), m_boardList(boardList)
{
    const auto boardPromptCallback = 
    [this](const BoardData& data, const BoardPromptContext& promptContext) {
        if (promptContext.boardIndex == -1) {
            m_boardList->AddElement(data);
            m_viewNavigation = OpenBoardView{ std::make_shared<Board>( data ) };
            return;
        }
        
        m_boardList->At(promptContext.boardIndex) = std::make_shared<BoardData>(data);
    };

    m_boardPrompt.SetOnExitCallback(boardPromptCallback);


    const auto boardPromptEventCallback = 
    [this](BoardPromptEventData data) {
        m_boardPrompt.Open(data.boardData, data.context);
    };

    m_boardPromptHandler = EventHandler<BoardPromptEventData>(boardPromptEventCallback);

    const auto deleteBoardEventCallback = 
    [this](DeleteBoardData data) {
        m_boardList->RemoveElement(data.index);
    };

    m_deleteBoardHandler = EventHandler<DeleteBoardData>(deleteBoardEventCallback);
}

void MainView::Update(float deltaTime) {
    m_boardPromptHandler.Update();
    m_deleteBoardHandler.Update();
}

void MainView::EventUpdate(const sf::Event &event) { 
    m_boardPrompt.EventUpdate(event);
}

ViewNavigation MainView::GetState() {
    return m_viewNavigation;
}