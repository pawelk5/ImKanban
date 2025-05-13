#include "pch.h"
#include "Core/EventHandler/EventHandler.hpp"
#include "MainView.hpp"


MainView::MainView() {
    ;
}

void MainView::Update(float deltaTime) {
    ;
}

void MainView::EventUpdate(const sf::Event &event) { 
    ;
}

bool MainView::GoToBoard() {
    return m_openBoard;
}

bool MainView::GoToImGuiDemo() {
    return m_openImGuiDemo;
}