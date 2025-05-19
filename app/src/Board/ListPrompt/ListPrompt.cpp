#include "pch.h"
#include "List.hpp"
#include "ListPrompt.hpp"

ListPrompt::ListPrompt() {
    m_open = false;
}

const char* ListPrompt::GetPopupID() {
    if (m_contextData.listIndex < 0)
        return Labels::newListPopup;
    
    return Labels::editListPopup;
}

void ListPrompt::DrawImpl(sf::RenderTarget& target) {
    ImGui::InputText("##Name", m_data.name.data(), m_data.name.size());
}

void ListPrompt::OpenImpl() {
    m_data.name.resize(UI::maxListNameSize);
}