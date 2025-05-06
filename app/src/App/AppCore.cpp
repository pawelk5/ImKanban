#include "Board.hpp"
#include "pch.h"
#include "App.hpp"

#include "Board/BoardView.hpp"


App::App() {
    InitWindow();
    if (!ImGui::SFML::Init(m_window, false))
        throw std::runtime_error("Couldn't init imgui!");
    LoadFont();
    
    m_currentView = std::make_unique<BoardView>(std::make_shared<Board>(BoardData{"example"}));
}

App::~App() {
    ImGui::SFML::Shutdown();
}

App& App::Get() {
    static App s_App{};
    return s_App;
}

void App::InitWindow() {
    m_window.create(sf::VideoMode::getDesktopMode(),
        PROJECT_NAME, sf::Style::Default, sf::State::Windowed);

    m_window.setVerticalSyncEnabled(true);
}

void App::LoadFont() {
    std::array<float, 2> fontSizes = {
        20.f, 24.f
    };

    auto& io = ImGui::GetIO();
    for (const auto& size : fontSizes)
        io.Fonts->AddFontFromFileTTF("assets/NotoSans.ttf", size);

    if (!ImGui::SFML::UpdateFontTexture())
        throw std::runtime_error("Couldn't update font texture!");
}