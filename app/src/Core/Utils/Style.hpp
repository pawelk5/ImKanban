#pragma once
#include "pch.h"
#include "Constants.hpp"


namespace Style {
    /// Executes the given lambda with selected font
    /// \param font font ID (from UI::Font enum)
    /// \param lambda callable that draws widgets using specified font
    template<typename T>
    void WithFont(UI::Font font, const T& lambda) {
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[(int)font]);
        lambda();
        ImGui::PopFont();
    }

    /// Type alias for ImGui style value
    /// Supported types: float, ImVec2
    using StyleValue = std::variant<float, ImVec2>;

    /// Type alias for ImGui style (style ID and value)
    using StylePair = std::pair<ImGuiStyleVar, StyleValue>;

    /// Executes the given lambda with additional style
    /// \param var ImGui style variable ID
    /// \param value Value of the style variable
    /// \param lambda callable that draws widgets using specified style
    template<typename T>
    void WithStyle(ImGuiStyleVar var, const StyleValue& value, const T& lambda) {
        std::visit([var](const auto& arg) {
            ImGui::PushStyleVar(var, arg);
        }, value);

        lambda();
        ImGui::PopStyleVar();
    }

    /// Executes the given lambda with additional styles
    /// \param styles vector of style pairs (style ID and value)
    /// \param lambda callable that draws widgets using specified style
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