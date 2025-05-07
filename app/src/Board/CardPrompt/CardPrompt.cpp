#include "pch.h"
#include "CardPrompt.hpp"


CardPrompt::CardPrompt() {
    m_open = false;
}

static const char* newCardPopupID = "New Task";
static const char* editCardPopupID = "Edit Task";

const char* CardPrompt::GetPopupID() {
    if (m_contextData.card < 0)
        return newCardPopupID;
    
    return editCardPopupID;
}

void CardPrompt::DrawImpl() {
    ImGui::InputText("Name", m_data.title.data(), m_data.title.size());
}

void CardPrompt::OpenImpl() {
    m_data.title.resize(255);
}