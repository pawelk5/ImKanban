#pragma once
#include "pch.h"
#include "Core/AppSettings/AppSettings.hpp"
#include "Board.hpp"


struct OpenMainView {};
struct OpenImGuiDemoView {};
struct OpenBoardView { std::shared_ptr<Board> pointer; };
struct OpenSettingsView {};


typedef std::optional<std::variant<OpenMainView, OpenImGuiDemoView, OpenBoardView, OpenSettingsView>> ViewNavigation;