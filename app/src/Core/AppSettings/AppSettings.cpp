#include "Core/Utils/Constants.hpp"
#include "pch.h"
#include <fstream>
#include <imgui.h>
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

AppSettings AppSettings::LoadFromFile(std::string filepath) {
    std::ifstream settingsFile;
    settingsFile.open(filepath);

    if (!settingsFile)
        return AppSettings{};

    AppSettings settings{};
    nlohmann::json data = nlohmann::json::parse(settingsFile);

    /// USEFUL LAMBDA FUNCTIONS
    const auto hasNumber = [data](const char* key) {
        return data.contains(key) && data[key].is_number_integer();
    };

    const auto inRange = [](int var, int min, int max) {
        return var >= min && var <= max;
    };


    if (hasNumber(AppDefs::settingsThemeKey)) {
        const auto theme = data[AppDefs::settingsThemeKey].template get<int>();
        if (inRange(theme, (int)UI::Theme::Light, (int)UI::Theme::COUNT - 1))
            settings.theme = (UI::Theme)theme;
    }

    if (hasNumber(AppDefs::settingsFontKey)) {
        const auto fontSize = data[AppDefs::settingsFontKey].template get<int>();
        if (inRange(fontSize, (int)UI::Font::Small, (int)UI::Font::Large))
            settings.fontSize = (UI::Font)fontSize;
    }
    
    settingsFile.close();
    return settings;
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