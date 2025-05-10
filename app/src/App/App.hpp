#pragma once
#include "pch.h"
#include "Core/View/ViewBase.hpp"

/// Main app class (IMPLEMENTED AS A SINGLETON)
class App {
public:
    /// Get the singleton instace of a class
    static App& Get();

    /// Remove copy constructor
    App(App const&) = delete;
    /// Remove assign constructor
    void operator=(App const&) = delete;

    /// Main app function, starts the main loop
    void Run();
    
private:
    /// Initializes application and ImGui
    App();

    /// Shuts down ImGui
    ~App();

    /// Creates and sets up a window
    void CreateWindow();

    /// Loads up fonts
    void LoadFont();
    
    /// Create the starting view of the app
    void CreateStartView();

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
};