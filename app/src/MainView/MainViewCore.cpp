#include "pch.h"
#include "Core/EventHandler/EventHandler.hpp"
#include "MainView.hpp"


MainView::MainView() 
    : m_viewNavigation(std::nullopt)
{
    ;
}

void MainView::Update(float deltaTime) {
    ;
}

void MainView::EventUpdate(const sf::Event &event) { 
    ;
}

ViewNavigation MainView::GetState() {
    return m_viewNavigation;
}