#include "pch.h"
#include "BoardPrompt.hpp"

BoardPrompt::BoardPrompt() {
    m_open = false;
}

const char* BoardPrompt::GetPopupID() {
    if (m_contextData.boardIndex < 0)
        return Labels::newBoardPopup;
    
    return Labels::editBoardPopup;
}

void BoardPrompt::DrawImpl(sf::RenderTarget& target) {
    ImGui::InputText("##Name", m_data.name.data(), m_data.name.size());
}

void BoardPrompt::OpenImpl() {
    m_data.name.resize(UI::maxBoardNameSize);
}