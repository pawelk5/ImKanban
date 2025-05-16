#include "Core/AppSettings/AppSettings.hpp"
#include "Core/Utils/Constants.hpp"
#include "pch.h"
#include "SettingsView.hpp"

SettingsView::SettingsView(AppSettings& appSettings) 
    :m_appSettingsRef(appSettings), m_appSettingsBeforeChanges(appSettings)
{
    ;
}

SettingsView::~SettingsView() {
    AppSettings::SaveToFile(m_appSettingsRef, AppDefs::settingsFile);
}

void SettingsView::Update(float deltaTime) {
    ;
}

void SettingsView::EventUpdate(const sf::Event &event) { 
    ;
}

ViewNavigation SettingsView::GetState() {
    return m_viewNavigation;
}