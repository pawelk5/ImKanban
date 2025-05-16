#pragma once
#include "Core/Utils/Constants.hpp"
#include <imgui.h>

/// Struct for holding current app settings
struct AppSettings {
    /// Current font size
    defs::UI::Font fontSize = defs::App::defaultFont;

    /// Current theme
    defs::UI::Theme theme = defs::App::defaultTheme;

    /// Get ID of the font relative to current ID
    /// \param diff difference in font size (e.g. +1 returns a larger font)
    /// \return A font size offset by diff, (in a valid range)
    defs::UI::Font GetFont(int diff) const;

    /// Sets theme variable and updates ImGui theme
    void SetTheme(defs::UI::Theme newTheme);

    /// Updates current ImGui theme
    void UpdateTheme() const;

    /// Applies all settings
    void Apply() const;

    /// Load settings from file
    /// \param filepath path to file
    /// \returns loaded app settings (or default app settings if loading failed)
    static AppSettings LoadFromFile(std::string filepath);

    /// Save settings to file
    /// \param filepath path to file
    static void SaveToFile(AppSettings settings, std::string filepath);
};