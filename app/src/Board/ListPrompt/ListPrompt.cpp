#include "pch.h"
#include "List.hpp"
#include "ListPrompt.hpp"

ListPrompt::ListPrompt() {
    m_open = false;
}

const char* ListPrompt::GetPopupID() {
    if (m_contextData.listIndex < 0)
        return defs::Labels::newListPopup;
    
    return defs::Labels::editListPopup;
}

void ListPrompt::DrawImpl(sf::RenderTarget& target) {
    ImGui::InputText("##Name", m_data.name.data(), m_data.name.size());
}

void ListPrompt::OpenImpl() {
    m_data.name.resize(defs::UI::maxListNameSize);
}