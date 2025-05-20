#pragma once
#include "pch.h"
#include <imgui.h>

namespace Widgets {
    /// Calculates hamburger menu button size
    ImVec2 GetHamburgerMenuSize();

    /// Calculates hamburger menu button size
    /// \param contentSize size of the button's content
    ImVec2 GetButtonSize(const ImVec2& contentSize);

    /// Calculates the size of ImGui Button
    /// \param label button label
    ImVec2 GetButtonSize(const char* label);

    /// Aligns next item to the right
    /// \param itemSize next item size
    void AlignNextItemRight(const ImVec2& itemSize);

    /// Aligns next item to the top right
    /// \param itemSize next item size
    void AlignNextItemTopRight(const ImVec2& itemSize);

    /// Creates hamburger menu button
    /// \returns true if button is clicked
    bool HamburgerMenu();
}