#include "Core/Utils/Constants.hpp"
#include "pch.h"
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

        m_openMainView = ImGui::Button(ICON_FA_HOUSE " Return", size);
    });
}

void SettingsView::DrawImpl(sf::RenderTarget& target) {
    ;
}

void SettingsView::DrawContent(sf::RenderTarget &target) {
    if (ImGui::BeginChild("##settings-container", ImGui::GetContentRegionAvail(), 
        defs::UIFlags::childFlags, defs::UIFlags::contentWindowFlags)) {
        ImGui::Text("Font Size");

        const ImVec2 size = { 80.f, 80.f };
        for (int i = (int)defs::UI::Font::Small; i <= (int)defs::UI::Font::Large; i++) {
            Style::WithFont((defs::UI::Font) i, 
            [this, size, i ]() {
                
                if (ImGui::Button(("Aa##" + std::to_string(i)).c_str(), size))
                    m_appSettingsRef.fontSize = (defs::UI::Font)i;
            });

            if (i != (int)defs::UI::Font::Large)
                ImGui::SameLine();
        }
    }
    ImGui::EndChild();
}

void SettingsView::DrawHeader() {
    ;
}