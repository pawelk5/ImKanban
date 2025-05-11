#pragma once
#include "Core/View/ViewBase.hpp"

/// draw imgui demo view
/// NOTE: ONLY FOR DEBUGGING
class ImGuiDemoView : public ViewBase {
public:
    explicit ImGuiDemoView();

    void DrawContent(sf::RenderTarget& target) override;
    void DrawSidebar(sf::RenderTarget& target) override;
    void DrawTopbar(sf::RenderTarget& target) override;
    void DrawImpl(sf::RenderTarget& target) override;

    void Update(float deltaTime) override;
    void EventUpdate(const sf::Event& event) override;

    bool GoToBoard();

private:
    bool m_goToBoard;
};