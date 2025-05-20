#include "Widgets.hpp"
#include "Core/Utils/Constants.hpp"
#include <imgui.h>

namespace Widgets {
    ImVec2 GetButtonSize(const ImVec2& contentSize) {
        auto& style = ImGui::GetStyle();

        return ImVec2{contentSize.x + 2 * style.FramePadding.x, contentSize.y + 2 * style.FramePadding.y};
    }

    ImVec2 GetButtonSize(const char* label) {
        return GetButtonSize(ImGui::CalcTextSize(label));
    }
    
    ImVec2 GetHamburgerMenuSize() {
        float value = std::max(ImGui::CalcTextSize(Labels::hamburgerMenu).x + ImGui::GetStyle().FramePadding.x * 2,
                            ImGui::GetTextLineHeightWithSpacing());

        return ImVec2(value, value);
    }

    bool HamburgerMenu() {
        return ImGui::Button(Labels::hamburgerMenu, GetHamburgerMenuSize());
    }

    void AlignNextItemRight(const ImVec2& itemSize) {
        ImGuiStyle& style = ImGui::GetStyle();
        const ImVec2 availableArea = ImGui::GetContentRegionAvail();
        const ImVec2 currentCursor = ImGui::GetCursorPos();
        
        ImVec2 newPos = { currentCursor.x + availableArea.x - itemSize.x,
                             currentCursor.y   };
        
        ImGui::SetCursorPos(newPos);
    }

    void AlignNextItemTopRight(const ImVec2& itemSize) {
        ImGuiStyle& style = ImGui::GetStyle();
        const ImVec2 availableArea = ImGui::GetContentRegionAvail();
        const ImVec2 currentCursor = ImGui::GetCursorStartPos();
        
        ImVec2 newPos = { currentCursor.x + availableArea.x - itemSize.x,
                             currentCursor.y };
        
        ImGui::SetCursorPos(newPos);
    }
}