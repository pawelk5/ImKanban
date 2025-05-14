#pragma once
#include "fontawesome/IconFontCppHeaders/IconsFontAwesome6.h"

namespace defs {
    namespace Labels {
        constexpr const char* okButtonLabel = ICON_FA_CHECK " OK";
        constexpr const char* cancelButtonLabel = ICON_FA_XMARK " Cancel";

        constexpr const char* newCardPopup = ICON_FA_SQUARE_PLUS " New Task";
        constexpr const char* editCardPopup = ICON_FA_PENCIL " Edit Task";

        constexpr const char* newListPopup = ICON_FA_SQUARE_PLUS " New List";
        constexpr const char* editListPopup = ICON_FA_PENCIL " Edit List";

        constexpr const char* addListLabel = ICON_FA_SQUARE_PLUS " Add List";
        constexpr const char* addTaskLabel = ICON_FA_SQUARE_PLUS " Add Task";

        constexpr const char* deleteItemLabel = ICON_FA_TRASH " Delete";
        constexpr const char* editItemLabel = ICON_FA_PENCIL " Edit";

        constexpr const char* confirmPromptLabel = ICON_FA_CHECK " Confirm";
        constexpr const char* deleteItemConfirmPromptMessage = "Are you sure you want to delete this item?";

        constexpr const char* mainViewContainerHeader = "Your boards";
    }

    namespace UI {
        /// Payload enum for drag and drop operations
        enum class PayloadType {
            CardDrag,
            ListDrag
        };
        
        /// Returns payload type ID (for ImGui)
        /// \param type payload type
        /// \return payload ID string
        constexpr const char* ToString(PayloadType type) {
            switch (type)
            {
            case PayloadType::CardDrag:
                return "CARD_DRAG";
            case PayloadType::ListDrag:
                return "LIST_DRAG";
            default:
                return "UNKNOWN_PAYLOAD";
            }
        }

        constexpr const int sizesCount = 3;
        constexpr const int fontsCount = 1;
        constexpr const std::array<float, sizesCount> fontSizes = {
            20.f, 24.f, 32.f
        };

        enum class Font {
            NORMAL_SMALL = 0,
            NORMAL_MEDIUM,
            NORMAL_LARGE,
            COUNT
        };

        static_assert((int)Font::COUNT == sizesCount * fontsCount);

        constexpr const int maxListNameSize = 32;
        constexpr const int maxCardNameSize = 48;
    }

    namespace UIFlags {
        /// Window flag for modal prompts
        constexpr const int promptFlags = 
                  ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_AlwaysAutoResize;

        /// Default window flags (no move/resize/collapse)
        constexpr const int windowFlags =
                  ImGuiWindowFlags_NoSavedSettings 
                | ImGuiWindowFlags_NoMove 
                | ImGuiWindowFlags_NoResize 
                | ImGuiWindowFlags_NoCollapse;
        
        /// windowFlags + horizontal scrollbar
        constexpr const int contentWindowFlags =
            windowFlags | ImGuiWindowFlags_HorizontalScrollbar;
        
        /// Flag for child windows
        constexpr const int childFlags =
            ImGuiChildFlags_FrameStyle | ImGuiChildFlags_Borders;
    }

    /// error strings
    namespace Error {
        constexpr const char* errorImGuiInit = "Couldn't init imgui!";
        constexpr const char* updateFontTexture = "Couldn't update font texture!";
    }
}