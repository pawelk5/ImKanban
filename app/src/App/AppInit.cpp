#include "App.hpp"
#include "pch.h"

App::App() {
    InitWindow();
    if (!ImGui::SFML::Init(m_window))
        throw std::runtime_error("Couldn't init imgui!");
}

void App::InitWindow() {
    m_window.create(sf::VideoMode::getDesktopMode(),
        PROJECT_NAME, sf::Style::Default, sf::State::Windowed);

    m_window.setVerticalSyncEnabled(true);
}