#pragma once
#include "Core/Utils/Constants.hpp"
#include "pch.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <imgui.h>

/// Virtual class for a view (managed by App class)
class ViewBase
{
public:
    virtual ~ViewBase() = default;

    /// Draws basic structure of the view (sidebar, topbar, popups and main content) to a SFML render target
    /// \param target SFML render target to draw on
    void Draw(sf::RenderTarget &target)
    {
        const float targetWidth = (float)target.getSize().x;
        const float targetHeight = (float)target.getSize().y;

        const ImGuiStyle currentStyle = ImGui::GetStyle();
        const float windowPadding = currentStyle.WindowPadding.x;

        const ImVec2 windowSize = {targetWidth, targetHeight};
        const ImVec2 leftRegionSize{windowSize.x * 0.15f - 2 * windowPadding, targetHeight};

        const ImVec2 mainRegionSize = {targetWidth - leftRegionSize.x, targetHeight};
        const ImVec2 mainRegionPos = {leftRegionSize.x, 0.f};

        const ImVec2 sidebarSize = {leftRegionSize.x - 2 * windowPadding, 0.f};
        const ImVec2 contentSize = {mainRegionSize.x - 2 * windowPadding, 0.f};

        ImGui::SetNextWindowSize(leftRegionSize);
        ImGui::SetNextWindowPos({0.f, 0.f});

        if (ImGui::Begin("##side-region", nullptr,
                         defs::UIFlags::windowFlags | ImGuiWindowFlags_NoTitleBar))
            DrawSidebar(target);
        ImGui::End();

        ImGui::SetNextWindowSize(mainRegionSize);
        ImGui::SetNextWindowPos(mainRegionPos);
        if (ImGui::Begin("##main-region", nullptr,
                         defs::UIFlags::windowFlags | ImGuiWindowFlags_NoTitleBar))
            DrawContent(target);
        ImGui::End();

        DrawImpl(target);
    }

    /// Update state of the view
    /// \param deltaTime time elapsed since last frame
    virtual void Update(float deltaTime) = 0;

    /// Handle an SFML event
    /// \param event SFML event to handle
    virtual void EventUpdate(const sf::Event &event) = 0;

protected:
    /// Draw contents of the sidebar
    /// \param target SFML render target to draw on
    virtual void DrawSidebar(sf::RenderTarget &target) = 0;

    /// Draw main content of the view
    /// \param target SFML render target to draw on
    virtual void DrawContent(sf::RenderTarget &target) = 0;

    /// Draw other things after view has been drawn
    /// \param target SFML render target to draw on
    virtual void DrawImpl(sf::RenderTarget &target) = 0;
};