#include "pch.h"
#include "CardPrompt.hpp"


CardPrompt::CardPrompt() {
    m_open = false;
}

static const char* popupID = "Card Prompt";

const char* CardPrompt::GetPopupID() {
    return popupID;
}

void CardPrompt::DrawImpl() {
    ImGui::InputText("Name", m_data.title.data(), m_data.title.size());
}

void CardPrompt::OpenImpl() {
    m_data.title.resize(255);
}