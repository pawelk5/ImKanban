#include "pch.h"
#include "App.hpp"

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

        if (event->is<sf::Event::Closed>()) {
            m_window.close();
            break;
        }

        if (event->is<sf::Event::Resized>()) {
            auto newSize = event->getIf<sf::Event::Resized>()->size;
            m_window.setView(sf::View(sf::FloatRect({0,0}, 
                (sf::Vector2f)newSize)));
        }

        m_currentView->EventUpdate(event.value());
    }
}

void App::Update() {
    auto deltaTime = m_clock.restart();
    ImGui::SFML::Update(m_window, deltaTime);
    m_currentView->Update(deltaTime.asSeconds());
}

void App::Draw() {
    m_window.clear();
    // for debuging
    ImGui::ShowDemoWindow();
    
    m_currentView->Draw(m_window);
    ImGui::SFML::Render(m_window);
    m_window.display();
}