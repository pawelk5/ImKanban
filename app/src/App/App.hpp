#pragma once
#include "pch.h"
#include "BoardList.hpp"
#include "Core/View/ViewBase.hpp"
#include "Core/AppSettings/AppSettings.hpp"

/// Main app class (IMPLEMENTED AS A SINGLETON)
class App {
public:
    /// Returns the singleton instance of a class
    static App& Get();

    /// Remove copy constructor
    App(App const&) = delete;
    /// Remove assign constructor
    void operator=(App const&) = delete;

    /// Main app function, starts the main loop
    void Run();
    
    /// Returns app settings (static version)
    static const AppSettings& Settings();

    /// Returns app settings
    const AppSettings& GetSettings();

private:
    /// Initializes application and ImGui
    App();

    /// Shuts down ImGui
    ~App();

private:
    /// Creates and sets up a window
    void CreateWindow();

    /// Loads up fonts
    void LoadFont();
    
private:
    /// Handles the logic for changing views
    void ChangeViewHandler();

    /// Create main view
    void CreateMainView();

    /// Create imgui demo view
    void CreateImGuiDemoView();

    /// Create board view
    /// \param boardViewData data required to create BoardView
    void CreateBoardView(const OpenBoardView& boardViewData);

    /// Create settings view
    void CreateSettingsView();

private:
    /// Handles all SFML events
    void EventUpdate();

    /// Updates clock and current view
    void Update();

    /// Renders current view to the window
    void Draw();

    /// Changes between fullscreen and floating window
    void ChangeFullscreenMode();

private:
    /// Main (and only) app window
    sf::RenderWindow m_window;

    /// Flag if the window is fullscreen (starts with false)
    bool m_isFullscreen;

    /// App clock
    sf::Clock m_clock;

    /// Current view
    std::unique_ptr<ViewBase> m_currentView;

    /// Current app settings
    AppSettings m_settings;

private:
    /// Board data container
    std::shared_ptr<BoardList> m_boardList;
};