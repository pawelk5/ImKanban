#include "App.hpp"
#include "pch.h"

App& App::Get() {
    static App s_App{};
    return s_App;
}

App::~App() {
    ImGui::SFML::Shutdown();
}