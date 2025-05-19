#include "pch.h"
#include "Core/Utils/Constants.hpp"
#include "AppSettings.hpp"

UI::Font AppSettings::GetFont(int diff) const {
    int currentFont = (int)fontSize;
    if (currentFont + diff < 0 || currentFont + diff <= 1)
        return (UI::Font)currentFont;

    return (UI::Font)(currentFont + diff);
}

void AppSettings::SetTheme(UI::Theme newTheme) {
    theme = newTheme;
    UpdateTheme();
}

/// (TODO: make custom themes)
void AppSettings::UpdateTheme() const {
    if (theme == UI::Theme::Light)
        ImGui::StyleColorsLight();
    else if (theme == UI::Theme::Dark)
        ImGui::StyleColorsDark();
}

void AppSettings::Apply() const {
    UpdateTheme();
}

void AppSettings::SaveToFile(AppSettings settings, std::string filepath) {
    std::ofstream settingsFile;
    settingsFile.open(filepath);

    if (!settingsFile)
        return;

    nlohmann::json settingsJson = {
        {AppDefs::settingsFontKey, settings.fontSize},
        {AppDefs::settingsThemeKey, settings.theme}
    };

    settingsFile << settingsJson.dump();

    settingsFile.close();
}