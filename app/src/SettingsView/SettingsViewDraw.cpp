#include "Core/ViewNavigation/ViewNavigation.hpp"
#include "pch.h"
#include "Core/Utils/Constants.hpp"
#include "SettingsView.hpp"
#include "Core/Utils/Style.hpp"
#include "App/App.hpp"
#include <imgui.h>

void SettingsView::DrawSidebar(sf::RenderTarget& target) {
    Style::WithFont(App::Settings().GetFont(+1), 
        [this](){
        ImGui::Text("%s Settings", ICON_FA_GEAR);
        ImGui::Separator();

        const ImVec2 size = ImVec2{ImGui::GetContentRegionAvail().x, 2*ImGui::GetTextLineHeightWithSpacing()};

        if (ImGui::Button(ICON_FA_HOUSE " Return", size))
            m_viewNavigation = OpenMainView();
    });
}

void SettingsView::DrawImpl(sf::RenderTarget& target) {
    ;
}

void SettingsView::DrawContent(sf::RenderTarget &target) {
    if (ImGui::BeginChild("##settings-container", ImGui::GetContentRegionAvail(), 
        UIFlags::childFlags, UIFlags::contentWindowFlags)) {
        ImGui::Text("Font Size");

        const ImVec2 size = { 80.f, 80.f };
        for (int i = (int)UI::Font::Small; i <= (int)UI::Font::Large; i++) {
            Style::WithFont((UI::Font) i, 
            [this, size, i ]() {
                
                if (ImGui::Button(("Aa##" + std::to_string(i)).c_str(), size))
                    m_appSettingsRef.fontSize = (UI::Font)i;
            });

            if (i != (int)UI::Font::Large)
                ImGui::SameLine();
        }
        
        ImGui::Separator();

        ImGui::Text("Theme");
        for (int i = (int)UI::Theme::Light; i < (int)UI::Theme::COUNT; i++) {
            if (ImGui::Button(UI::themes[i], size))
                m_appSettingsRef.SetTheme((UI::Theme)i);
            if (i != (int)UI::Font::COUNT - 1)
                ImGui::SameLine();
        }
    }
    ImGui::EndChild();
}

void SettingsView::DrawHeader() {
    ;
}