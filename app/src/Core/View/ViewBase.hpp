#pragma once
#include "pch.h"

/// Virtual class for a view (managed by App class)
class ViewBase {
public:
    virtual ~ViewBase() = default;

    virtual void Draw(sf::RenderTarget& target) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void EventUpdate(const sf::Event& event) = 0;
};