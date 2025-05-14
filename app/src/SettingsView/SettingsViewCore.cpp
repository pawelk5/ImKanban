#include "pch.h"
#include "SettingsView.hpp"

SettingsView::SettingsView(AppSettings& appSettings) 
    :m_appSettingsRef(appSettings)
{
    ;
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