#include "pch.h"
#include "List.hpp"
#include "ListPrompt.hpp"

ListPrompt::ListPrompt() {
    m_open = false;
}

static const char* popupID = "New List";

const char* ListPrompt::GetPopupID() {
    return popupID;
}

void ListPrompt::DrawImpl() {
    ImGui::InputText("Name", m_data.name.data(), m_data.name.size());
}

void ListPrompt::OpenImpl() {
    m_data.name.resize(255);
}