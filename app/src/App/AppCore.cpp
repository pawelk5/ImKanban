#include "Board.hpp"
#include "Core/Utils/Constants.hpp"
#include "pch.h"
#include "App.hpp"

#include "Board/BoardView.hpp"


App::App()
    :m_isFullscreen(false)
{
    CreateWindow();
    if (!ImGui::SFML::Init(m_window, false))
        throw std::runtime_error(defs::Error::errorImGuiInit);
    LoadFont();
    
    CreateStartView();    
}

App::~App() {
    ImGui::SFML::Shutdown();
}

App& App::Get() {
    static App s_App{};
    return s_App;
}

void App::CreateWindow() {
    m_window.create(sf::VideoMode::getDesktopMode(),
        PROJECT_NAME, sf::Style::Default, m_isFullscreen ? sf::State::Fullscreen : sf::State::Windowed);
    
    m_window.setVerticalSyncEnabled(true);
}

void App::LoadFont() {
    auto& io = ImGui::GetIO();

    /// NOTE: THIS IS FONT SPECIFIC!
    /// unicode ranges
    constexpr const ImWchar ranges[] = {
        0x0020, 0x00FF, // basic
        0x0100, 0x017F, // latin extended a
        0x0180, 0x024F, // latin extended b
        0x0370, 0x03FF, // greek
        0x0400, 0x04FF, // cyrillic
        0x2000, 0x206F, // punctuation
        0x20A0, 0x20CF, // currency symbols
        0,
    };

    for (const auto& size : defs::UI::fontSizes)
        io.Fonts->AddFontFromFileTTF("assets/NotoSans.ttf", size, 
            nullptr, ranges);

    if (!ImGui::SFML::UpdateFontTexture())
        throw std::runtime_error(defs::Error::updateFontTexture);
}

void App::CreateStartView() {
    m_currentView = std::make_unique<BoardView>(std::make_shared<Board>(BoardData{"example"}));
}

void App::ChangeFullscreenMode() {
    m_isFullscreen = !m_isFullscreen;
    
    m_window.close();
    CreateWindow();
}