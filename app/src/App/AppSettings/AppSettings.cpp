#include "pch.h"
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
    AppSettings settings{};


    return settings;
}

void AppSettings::SaveToFile(AppSettings settings, std::string filepath) {
    ;
}