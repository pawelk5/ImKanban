#pragma once
#include "pch.h"
#include "Constants.hpp"


namespace Style {
    template<typename T>
    void WithFont(defs::UI::Font font, const T& lambda) {
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[(int)font]);
        lambda();
        ImGui::PopFont();
    }


    using StyleValue = std::variant<float, ImVec2>;
    using StylePair = std::pair<ImGuiStyleVar, StyleValue>;

    template<typename T>
    void WithStyle(ImGuiStyleVar var, const StyleValue& style, const T& lambda) {
        std::visit([var](const auto& arg) {
            ImGui::PushStyleVar(var, arg);
        }, style);

        lambda();
        ImGui::PopStyleVar();
    }

    template<typename T>
    void WithStyles(const std::vector<StylePair>& styles, const T& lambda) {
        for (const auto& [var, value] : styles) {
            std::visit([var](const auto& arg) {
                ImGui::PushStyleVar(var, arg);
            }, value);
        }

        lambda();
        ImGui::PopStyleVar(styles.size());
    }
}