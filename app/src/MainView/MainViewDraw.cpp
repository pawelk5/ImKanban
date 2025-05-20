#include "pch.h"
#include "Core/ViewNavigation/ViewNavigation.hpp"
#include "Board.hpp"
#include "Core/Utils/Style.hpp"
#include "MainView.hpp"
#include "App/App.hpp"
#include <imgui.h>



void MainView::DrawSidebar(sf::RenderTarget& target) {
    Style::WithFont(App::Settings().GetFont(+1), 
        [this](){
        ImGui::Text("%s", PROJECT_NAME);
        ImGui::Separator();

        const ImVec2 size = ImVec2{ImGui::GetContentRegionAvail().x, 2*ImGui::GetTextLineHeightWithSpacing()};

        if (ImGui::Button(ICON_FA_GEAR " Settings", size))
            m_viewNavigation = OpenSettingsView{ };
        if (ImGui::Button(ICON_FA_BUG " Open ImGui Demo", size))
            m_viewNavigation = OpenImGuiDemoView();
    });
}

void MainView::DrawImpl(sf::RenderTarget& target) {
    m_boardPrompt.Draw(target);
}

void MainView::DrawContent(sf::RenderTarget &target) {
    DrawHeader();
    ImGui::Separator();
    if (ImGui::BeginChild("##boards-container", ImGui::GetContentRegionAvail(), 
        UIFlags::childFlags, UIFlags::contentWindowFlags)) {
        const auto area = ImGui::GetContentRegionAvail();
        const int boardsPerRow = floor(area.x / 300.f);
        const float width = (area.x - boardsPerRow * ImGui::GetStyle().ItemSpacing.x) / boardsPerRow;

        DrawBoards(boardsPerRow, width);

    }
    ImGui::EndChild();
}

void MainView::DrawBoards(int boardsPerRow, float width) {
    const auto &dataRef = m_boardList->GetElementArray();
    const ImVec2 childSize = ImVec2{width, 300.f};

    for (auto it = dataRef.begin(); it < dataRef.end(); ++it) {
        const auto itemIndex = m_boardList->AsIndex(it);
        const auto& item = m_boardList->At(it);

        if (ImGui::BeginChild(std::to_string(itemIndex).c_str(), childSize, 
            UIFlags::childFlags, UIFlags::windowFlags)){
        
            Style::WithFont(App::Settings().GetFont(+1),
                [&]() {
                ImGui::Text("%s", item->name.c_str());

                if (ImGui::Button("Open"))
                    m_viewNavigation = OpenBoardView{ std::make_shared<Board>( *(*it) ) };
                if (ImGui::Button("Edit"))
                    m_boardPromptHandler.Trigger(
                        BoardPromptEventData{ {*(*it)}, { itemIndex }}
                    );
                if (ImGui::Button("Delete"))
                    m_deleteBoardHandler.Trigger({ itemIndex });
            });
            
        }
        ImGui::EndChild();

        if ((itemIndex + 1) % boardsPerRow != 0)
            ImGui::SameLine();
    }
}

void MainView::DrawHeader() {
    Style::WithFont(App::Settings().GetFont(+2),
        [this]() {
        ImGui::Text("%s", Labels::mainViewContainerHeader);
        if (ImGui::Button(Labels::newBoardButton))
            m_boardPromptHandler.Trigger({ { std::nullopt }, {-1} });
    });

}