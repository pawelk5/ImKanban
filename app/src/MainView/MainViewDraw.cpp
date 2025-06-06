#include "Core/Utils/Constants.hpp"
#include "pch.h"
#include "Core/Widgets/Widgets.hpp"
#include "Core/ViewNavigation/ViewNavigation.hpp"
#include "Board.hpp"
#include "Core/Utils/Style.hpp"
#include "MainView.hpp"
#include "App/App.hpp"
#include <imgui.h>

void MainView::DrawSidebar(sf::RenderTarget &target)
{
    Style::WithFont(App::Settings().GetFont(+1),
                    [this]()
                    {
                        ImGui::Text("%s", PROJECT_NAME);
                        ImGui::Separator();

                        const ImVec2 size = ImVec2{ImGui::GetContentRegionAvail().x, 2 * ImGui::GetTextLineHeightWithSpacing()};

                        if (ImGui::Button(ICON_FA_GEAR " Settings", size))
                            m_viewNavigation = OpenSettingsView{};
                        if (ImGui::Button(ICON_FA_BUG " Open ImGui Demo", size))
                            m_viewNavigation = OpenImGuiDemoView();
                    });
}

void MainView::DrawImpl(sf::RenderTarget &target)
{
    m_boardPrompt.Draw(target);
}

void MainView::DrawContent(sf::RenderTarget &target)
{
    DrawHeader();
    ImGui::Separator();
    if (ImGui::BeginChild("##boards-container", ImGui::GetContentRegionAvail(),
                          UIFlags::childFlags, UIFlags::contentWindowFlags))
    {
        const auto area = ImGui::GetContentRegionAvail();
        const int boardsPerRow = floor(area.x / 300.f);
        const float width = (area.x - boardsPerRow * ImGui::GetStyle().ItemSpacing.x) / boardsPerRow;

        DrawBoards(boardsPerRow, width);
    }
    ImGui::EndChild();
}

void MainView::DrawBoards(int boardsPerRow, float width)
{
    const auto &dataRef = m_boardList->GetElementArray();
    const ImVec2 childSize = ImVec2{width, 300.f};

    for (auto it = dataRef.begin(); it < dataRef.end(); ++it)
    {
        const auto itemIndex = m_boardList->AsIndex(it);
        const auto &item = m_boardList->At(it);
        bool popupOpened = false;
        if (ImGui::BeginChild(std::to_string(itemIndex).c_str(), childSize,
                              UIFlags::childFlags, UIFlags::windowFlags))
        {

            DrawBoardContent(itemIndex);
        }
        ImGui::EndChild();

        if ((itemIndex + 1) % boardsPerRow != 0)
            ImGui::SameLine();
    }
}

void MainView::DrawBoardContent(int itemIndex)
{
    auto &item = m_boardList->At(itemIndex); //->fromJSON();
    bool popupOpened = false;

    Style::WithFont(App::Settings().GetFont(+1),
                    [&]()
                    {
        ImGui::Text("%s", item->name.c_str());
        
        ImVec2 buttonSize = Widgets::GetHamburgerMenuSize();
        Widgets::AlignNextItemTopRight(buttonSize);
        ImVec2 currentPos = ImGui::GetCursorScreenPos();
        if (Widgets::HamburgerMenu())
            ImGui::OpenPopup("hamburgerMenu");
        
        ImGui::SetNextWindowPos({ currentPos.x + buttonSize.x / 2.f, currentPos.y + buttonSize.y / 2.f});
        if ((popupOpened = ImGui::BeginPopupContextWindow("hamburgerMenu"))) {
            if (ImGui::Button("Edit"))
                m_boardPromptHandler.Trigger(
                    BoardPromptEventData{{ *item }, { itemIndex }}
                );
            if (ImGui::Button("Delete"))
                m_deleteBoardHandler.Trigger({ itemIndex });

            ImGui::EndPopup();
        } });

    /// Clicking empty space between buttons opens the board
    /// Uses filename-based constructor for automatic JSON handling
    if (ImGui::IsWindowHovered() &&
        ImGui::IsMouseClicked(ImGuiMouseButton_Left) &&
        !ImGui::IsAnyItemHovered() &&
        !popupOpened)
        m_viewNavigation = OpenBoardView{std::make_shared<Board>(item->filename)};
}

void MainView::DrawHeader()
{
    Style::WithFont(App::Settings().GetFont(+2),
                    [this]()
                    {
                        ImVec2 availableArea = ImGui::GetContentRegionAvail();

                        ImGui::Text("%s", Labels::mainViewContainerHeader);
                        ImGui::SameLine();

                        ImGuiStyle &style = ImGui::GetStyle();

                        ImVec2 buttonSize = Widgets::GetButtonSize(Labels::newBoardButton);

                        Widgets::AlignNextItemRight(buttonSize);
                        if (ImGui::Button(Labels::newBoardButton, buttonSize))
                            m_boardPromptHandler.Trigger({{std::nullopt}, {-1}});
                    });
}