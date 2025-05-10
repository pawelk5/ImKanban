#pragma once

namespace defs {
    namespace Labels {
        constexpr const char* okButtonLabel = "OK";
        constexpr const char* cancelButtonLabel = "Cancel";

        constexpr const char* newCardPopup = "New Task";
        constexpr const char* editCardPopup = "Edit Task";

        constexpr const char* newListPopup = "New List";
        constexpr const char* editListPopup = "Edit List";

        constexpr const char* addListLabel = "Add List";
        constexpr const char* addTaskLabel = "Add Task";

        constexpr const char* deleteItemLabel = "Delete";
        constexpr const char* editItemLabel = "Edit";
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

    }

    namespace UIFlags {
        /// Window flag for modal prompts
        static constexpr int promptFlags = 
                  ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_AlwaysAutoResize;

        /// Default window flags (no move/resize/collapse)
        static constexpr int windowFlags =
                  ImGuiWindowFlags_NoSavedSettings 
                | ImGuiWindowFlags_NoMove 
                | ImGuiWindowFlags_NoResize 
                | ImGuiWindowFlags_NoCollapse;
        
        /// windowFlags + horizontal scrollbar
        static constexpr int boardWindowFlags =
            windowFlags | ImGuiWindowFlags_HorizontalScrollbar;
        
        /// Flag for child windows
        static constexpr int childFlags =
            ImGuiChildFlags_FrameStyle | ImGuiChildFlags_Borders;
    }
}