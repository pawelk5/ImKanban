#pragma once
#include "pch.h"
#include "Board.hpp"
#include "BoardList.hpp"

/// Struct for changing view to MainView
struct OpenMainView {};

/// Struct for changing view to ImGuiDemoView
struct OpenImGuiDemoView {};

/// Struct for changing view to BoardView
struct OpenBoardView { 
    std::shared_ptr<Board> pointer;
};

/// Struct for changing view to SettingsView
struct OpenSettingsView {};

/// Type alias for optional variant of OpenView structs
using ViewNavigation = std::optional<std::variant<OpenMainView, OpenImGuiDemoView, OpenBoardView, OpenSettingsView>>;