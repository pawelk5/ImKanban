#include "App/AppSettings/AppSettings.hpp"
#include "pch.h"
#include "MainView/MainView.hpp"
#include "App.hpp"
#include "Core/Utils/Constants.hpp"
#include "Board/BoardView.hpp"
#include "ImGuiDemoView/ImGuiDemoView.hpp"
#include "SettingsView/SettingsView.hpp"
#include "notosans/noto.embed"
#include "fontawesome/fontawesome.embed"


App::App()
    :m_isFullscreen(false), m_settings()
{
    CreateWindow();
    if (!ImGui::SFML::Init(m_window, false))
        throw std::runtime_error(defs::Error::errorImGuiInit);
    LoadFont();
    
    CreateMainView();

    m_settings = AppSettings::LoadFromFile(defs::App::settingsFile);
}

App::~App() {
    ImGui::SFML::Shutdown();
}

App& App::Get() {
    static App s_App{};
    return s_App;
}

const AppSettings& App::GetSettings() {
    return m_settings;
}

const AppSettings& App::Settings() {
    return App::Get().GetSettings();
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
    constexpr const ImWchar notoRanges[] = {
        0x0020, 0x00FF, // basic
        0x0100, 0x017F, // latin extended a
        0x0180, 0x024F, // latin extended b
        0x0370, 0x03FF, // greek
        0x0400, 0x04FF, // cyrillic
        0x2000, 0x206F, // punctuation
        0x20A0, 0x20CF, // currency symbols
        0,
    };

    constexpr const ImWchar fontawesomeRanges[] = {
        ICON_MIN_FA, ICON_MAX_FA,
        0,
    };

    ImFontConfig fontawesomeConfig{};
    fontawesomeConfig.MergeMode = true;
    fontawesomeConfig.GlyphMinAdvanceX = 13.0f;
    
    ImFontConfig notoConfig{};
    notoConfig.MergeMode = false;


    notoConfig.FontDataOwnedByAtlas = false;
    fontawesomeConfig.FontDataOwnedByAtlas = false;

    for (const auto& size : defs::UI::fontSizes) {
        io.Fonts->AddFontFromMemoryTTF((void*)notoFont, notoFontSize, size, 
            &notoConfig, notoRanges);


        io.Fonts->AddFontFromMemoryTTF((void*)fontawesomeFont, fontawesomeFontSize, size, 
            &fontawesomeConfig, fontawesomeRanges);
    }

    if (!ImGui::SFML::UpdateFontTexture())
        throw std::runtime_error(defs::Error::updateFontTexture);
}

void App::CreateMainView() {
    m_currentView = std::make_unique<MainView>();
}

void App::CreateImGuiDemoView() {
    m_currentView = std::make_unique<ImGuiDemoView>();
}

void App::CreateBoardView() {
    m_currentView = std::make_unique<BoardView>(std::make_shared<Board>(BoardData{"example"}));
}

void App::CreateSettingsView() {
    m_currentView = std::make_unique<SettingsView>(m_settings);
}


void App::ChangeFullscreenMode() {
    m_isFullscreen = !m_isFullscreen;
    
    m_window.close();
    CreateWindow();
}


void App::ChangeViewHandler() {
    if (auto view = dynamic_cast<ImGuiDemoView*>(m_currentView.get())) {
        if (view->GoToMainView())
            CreateMainView();
    }
    else if (auto view = dynamic_cast<BoardView*>(m_currentView.get())) {
        if (view->GoToMainView())
            CreateMainView();
    }
    else if (auto view = dynamic_cast<SettingsView*>(m_currentView.get())) {
        if (view->GoToMainView())
            CreateMainView();
    }
    else if (auto view = dynamic_cast<MainView*>(m_currentView.get())) {
        if (view->GoToBoard())
            CreateBoardView();
        else if (view->GoToImGuiDemo())
            CreateImGuiDemoView();
        else if (view->GoToSettings())
            CreateSettingsView();
    }
}