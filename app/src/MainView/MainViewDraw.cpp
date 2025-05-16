#include "pch.h"
#include "Core/Utils/Style.hpp"
#include "MainView.hpp"
#include "App/App.hpp"

void MainView::DrawSidebar(sf::RenderTarget& target) {
    Style::WithFont(App::Settings().GetFont(+1), 
        [this](){
        ImGui::Text("%s", PROJECT_NAME);
        ImGui::Separator();

        const ImVec2 size = ImVec2{ImGui::GetContentRegionAvail().x, 2*ImGui::GetTextLineHeightWithSpacing()};

        m_openBoard = ImGui::Button(ICON_FA_CHALKBOARD " Open Board", size);
        m_openSettings = ImGui::Button(ICON_FA_GEAR " Settings", size);
        m_openImGuiDemo = ImGui::Button(ICON_FA_BUG " Open ImGui Demo", size);
    });
}

void MainView::DrawImpl(sf::RenderTarget& target) {

}

void MainView::DrawContent(sf::RenderTarget &target) {
    DrawHeader();
    ImGui::Separator();
    if (ImGui::BeginChild("##boards-container", ImGui::GetContentRegionAvail(), 
        UIFlags::childFlags, UIFlags::contentWindowFlags)) {
        
    }
    ImGui::EndChild();
}

void MainView::DrawHeader() {
    Style::WithFont(App::Settings().GetFont(+2),
        [this]() {
        ImGui::Text("%s", Labels::mainViewContainerHeader);
    });
}