#pragma once
#include "Core/Utils/Constants.hpp"

/// Struct for holding current app settings
struct AppSettings {
    /// Current font size
    defs::UI::Font fontSize = defs::UI::Font::Small;

    /// Get ID of the font relative to current ID
    /// \param diff difference in font size (e.g. +1 returns a larger font)
    /// \return A font size offset by diff, (in a valid range)
    defs::UI::Font GetFont(int diff) const {
        int currentFont = (int)fontSize;
        if (currentFont + diff < 0 || currentFont + diff <= 1)
            return (defs::UI::Font)currentFont;

        return (defs::UI::Font)(currentFont + diff);
    }
};