#include "pch.h"
#include "CardPrompt.hpp"


CardPrompt::CardPrompt() {
    m_open = false;
}

const char* CardPrompt::GetPopupID() {
    if (m_contextData.card < 0)
        return defs::Labels::newCardPopup;
    
    return defs::Labels::editCardPopup;
}

void CardPrompt::DrawImpl() {
    ImGui::InputText("Name", m_data.title.data(), m_data.title.size());
}

void CardPrompt::OpenImpl() {
    m_data.title.resize(255);
}