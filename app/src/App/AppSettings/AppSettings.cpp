#include "Core/Utils/Constants.hpp"
#include "pch.h"
#include <fstream>
#include <imgui.h>
#include "AppSettings.hpp"

defs::UI::Font AppSettings::GetFont(int diff) const {
    int currentFont = (int)fontSize;
    if (currentFont + diff < 0 || currentFont + diff <= 1)
        return (defs::UI::Font)currentFont;

    return (defs::UI::Font)(currentFont + diff);
}

void AppSettings::SetTheme(defs::UI::Theme newTheme) {
    theme = newTheme;
    UpdateTheme();
}

/// (TODO: make custom themes)
void AppSettings::UpdateTheme() const {
    if (theme == defs::UI::Theme::Light)
        ImGui::StyleColorsLight();
    else if (theme == defs::UI::Theme::Dark)
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


    if (hasNumber(defs::App::settingsThemeKey)) {
        const auto theme = data[defs::App::settingsThemeKey].template get<int>();
        if (inRange(theme, (int)defs::UI::Theme::Light, (int)defs::UI::Theme::COUNT - 1))
            settings.theme = (defs::UI::Theme)theme;
    }

    if (hasNumber(defs::App::settingsFontKey)) {
        const auto fontSize = data[defs::App::settingsFontKey].template get<int>();
        if (inRange(fontSize, (int)defs::UI::Font::Small, (int)defs::UI::Font::Large))
            settings.fontSize = (defs::UI::Font)fontSize;
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
        {defs::App::settingsFontKey, settings.fontSize},
        {defs::App::settingsThemeKey, settings.theme}
    };

    settingsFile << settingsJson.dump();

    settingsFile.close();
}