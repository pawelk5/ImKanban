#include "pch.h"
#include "App.hpp"

#include "Board/BoardView.hpp"


App::App() {
    InitWindow();
    if (!ImGui::SFML::Init(m_window))
        throw std::runtime_error("Couldn't init imgui!");
    
    m_currentScreen = std::make_unique<BoardView>(std::make_shared<Board>("example")); 
}

void App::InitWindow() {
    m_window.create(sf::VideoMode::getDesktopMode(),
        PROJECT_NAME, sf::Style::Default, sf::State::Windowed);

    m_window.setVerticalSyncEnabled(true);
}