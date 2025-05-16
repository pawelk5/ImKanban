#pragma once
#include "Core/AppSettings/AppSettings.hpp"
#include "Core/View/ViewBase.hpp"

/// View displaying application settings
class SettingsView : public ViewBase {
public:
    /// Constructs main view
    explicit SettingsView(AppSettings& appSettings);

    /// Destructs settings view
    /// \note saves settings to file
    ~SettingsView();

    /// Draw board in the main container
    /// \param target SFML render target
    void DrawContent(sf::RenderTarget& target) override;

    /// Draw main container header
    void DrawHeader();

    /// Draw sidebar content
    /// \param target SFML render target to draw on
    void DrawSidebar(sf::RenderTarget& target) override;

    /// Draw popups
    /// \param target SFML render target to draw on
    void DrawImpl(sf::RenderTarget& target) override;

    /// Update function to be called every frame
    /// \param deltaTime time passed since last frame
    void Update(float deltaTime) override;

    /// Event Update function to be called every time a SFML event took place
    /// \param event SFML event
    void EventUpdate(const sf::Event& event) override;

public:
    /// Getter function for m_openMainView
    bool GoToMainView();

private:
    bool m_openMainView;
    
    /// Reference to apps settings
    AppSettings& m_appSettingsRef;

    /// Settings before making changes
    const AppSettings m_appSettingsBeforeChanges;
};