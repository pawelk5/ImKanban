#include "pch.h"
#include "BoardList.hpp"
#include "Core/ViewNavigation/ViewNavigation.hpp"
#include "Core/AppSettings/AppSettings.hpp"
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
    
    m_boardList = std::make_shared<BoardList>(BoardListData {AppDefs::settingsFile} );
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
    m_currentView = std::make_unique<MainView>( m_boardList );
}

void App::CreateImGuiDemoView() {
    m_currentView = std::make_unique<ImGuiDemoView>();
}

void App::CreateBoardView(const OpenBoardView& boardViewData) {
    m_currentView = std::make_unique<BoardView>(boardViewData.pointer);
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
    if (auto state = m_currentView->GetState()) {
        if (std::holds_alternative<OpenBoardView>(*state)){
            auto data = std::get<OpenBoardView>(*state);
            CreateBoardView(data);
        }
        else if (std::holds_alternative<OpenImGuiDemoView>(*state))
            CreateImGuiDemoView();
        else if (std::holds_alternative<OpenSettingsView>(*state))
            CreateSettingsView();
        else if (std::holds_alternative<OpenMainView>(*state))
            CreateMainView();
    }
}