#pragma once
#include "Core/Utils/Constants.hpp"
#include <imgui.h>

/// Struct for holding current app settings
struct AppSettings {
    /// Current font size
    defs::UI::Font fontSize = defs::UI::Font::Small;

    /// Current theme
    defs::UI::Theme theme = defs::UI::Theme::Dark;

    /// Get ID of the font relative to current ID
    /// \param diff difference in font size (e.g. +1 returns a larger font)
    /// \return A font size offset by diff, (in a valid range)
    defs::UI::Font GetFont(int diff) const {
        int currentFont = (int)fontSize;
        if (currentFont + diff < 0 || currentFont + diff <= 1)
            return (defs::UI::Font)currentFont;

        return (defs::UI::Font)(currentFont + diff);
    }

    /// Sets theme variable and updates ImGui theme
    void SetTheme(defs::UI::Theme newTheme) {
        theme = newTheme;
        UpdateTheme();
    }

    /// Updates current ImGui theme
    /// (TODO: make custom themes)
    void UpdateTheme() const {
        if (theme == defs::UI::Theme::Light)
            ImGui::StyleColorsLight();
        else if (theme == defs::UI::Theme::Dark)
            ImGui::StyleColorsDark();
    }
};