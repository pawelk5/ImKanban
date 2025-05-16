#include "pch.h"
#include "App/AppSettings/AppSettings.hpp"
#include "MainView/MainView.hpp"
#include "App.hpp"
#include "Core/Utils/Constants.hpp"
#include "Board/BoardView.hpp"
#include "ImGuiDemoView/ImGuiDemoView.hpp"
#include "SettingsView/SettingsView.hpp"


App::App()
    :m_isFullscreen(false), m_settings()
{
    CreateWindow();
    if (!ImGui::SFML::Init(m_window, false))
        throw std::runtime_error(Error::errorImGuiInit);
    LoadFont();
    
    CreateMainView();

    m_settings = AppSettings::LoadFromFile(AppDefs::settingsFile);
    m_settings.Apply();
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