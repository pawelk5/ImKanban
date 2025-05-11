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

        // Handle resize event
        if (auto resized = event->getIf<sf::Event::Resized>())
            m_window.setView(sf::View(sf::FloatRect({0,0}, 
                (sf::Vector2f)resized->size)));


        if (auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::F11)
                ChangeFullscreenMode();
        }

        m_currentView->EventUpdate(event.value());
    }
}

void App::Update() {
    auto deltaTime = m_clock.restart();
    ImGui::SFML::Update(m_window, deltaTime);
    m_currentView->Update(deltaTime.asSeconds());
    
    
    ChangeViewHandler();
}

void App::Draw() {
    m_window.clear();
    m_currentView->Draw(m_window);
    ImGui::SFML::Render(m_window);
    m_window.display();
}