#include "App.hpp"
#include "pch.h"

void App::Run() {
    while (m_window.isOpen()) {
        EventUpdate();
        Update();
        Draw();
    }
}

void App::EventUpdate() {
    while (const auto event = m_window.pollEvent()) {
        ImGui::SFML::ProcessEvent(m_window, *event);

        if (event->is<sf::Event::Closed>()){
            m_window.close();
            break;
        }

        if (event->is<sf::Event::Resized>()){
            auto newSize = event->getIf<sf::Event::Resized>()->size;
            m_window.setView(sf::View(sf::FloatRect({0,0}, 
                (sf::Vector2f)newSize)));
        }
    }
}

void App::Update() {
    auto deltaTime = m_clock.restart();
    ImGui::SFML::Update(m_window, deltaTime);
}

void App::Draw() {
    m_window.clear();
    ImGui::ShowDemoWindow();
    ImGui::SFML::Render(m_window);
    m_window.display();
}