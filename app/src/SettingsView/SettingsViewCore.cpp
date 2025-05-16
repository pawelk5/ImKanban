#include "App/AppSettings/AppSettings.hpp"
#include "Core/Utils/Constants.hpp"
#include "pch.h"
#include "SettingsView.hpp"

SettingsView::SettingsView(AppSettings& appSettings) 
    :m_appSettingsRef(appSettings), m_appSettingsBeforeChanges(appSettings)
{
    ;
}

SettingsView::~SettingsView() {
    AppSettings::SaveToFile(m_appSettingsRef, defs::App::settingsFile);
}

void SettingsView::Update(float deltaTime) {
    ;
}

void SettingsView::EventUpdate(const sf::Event &event) { 
    ;
}

bool SettingsView::GoToMainView() {
    return m_openMainView;
}