#pragma once
#include "pch.h"

/// Virtual class for a view (managed by App class)
class ViewBase {
public:
    virtual ~ViewBase() = default;

    /// Draws view to a SFML render target
    /// \param target SFML render target to draw on
    virtual void Draw(sf::RenderTarget& target) = 0;

    /// Update state of the view
    /// \param deltaTime time elapsed since last frame
    virtual void Update(float deltaTime) = 0;
    
    /// Handle an SFML event
    /// \param event SFML event to handle
    virtual void EventUpdate(const sf::Event& event) = 0;
};