#pragma once
#include "Core/View/ViewBase.hpp"

/// View displaying a board's content
class MainView : public ViewBase {
public:
    /// Constructs main view
    explicit MainView();

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

    ViewNavigation GetState() override;

private:
    ViewNavigation m_viewNavigation;
};