#include "pch.h"
#include "Core/Utils/Constants.hpp"
#include "AppSettings.hpp"

/// Check if key is in json data
bool HasNumber(const nlohmann::json& data, const char* key) {
    return data.contains(key) && data[key].is_number_integer();
};

/// Check if variable is in range
constexpr bool InRange(int var, int min, int max) {
    return var >= min && var <= max;
};

/// Returns number if key exists and contains an integer
std::optional<int> GetNumber(nlohmann::json& data, const char* key) {
    return (data.contains(key) && data[key].is_number_integer()) 
        ? data[key].template get<int>() : std::optional<int>(std::nullopt);
}

AppSettings AppSettings::LoadFromFile(std::string filepath) {
    std::ifstream settingsFile;
    settingsFile.open(filepath);

    if (!settingsFile)
        return AppSettings{};

    AppSettings settings{};
    nlohmann::json data = nlohmann::json::parse(settingsFile);


    if (const auto theme = GetNumber(data, AppDefs::settingsThemeKey))
        if (InRange(*theme, (int)UI::Theme::Light, (int)UI::Theme::COUNT - 1))
            settings.theme = (UI::Theme)*theme;

    if (const auto fontSize = GetNumber(data, AppDefs::settingsFontKey))
        if (InRange(*fontSize, (int)UI::Font::Small, (int)UI::Font::Large))
            settings.fontSize = (UI::Font)*fontSize;
    
    settingsFile.close();
    return settings;
}