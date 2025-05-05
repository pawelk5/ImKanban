#include "pch.h"
#include "List.hpp"
#include "ListPrompt.hpp"

ListPrompt::ListPrompt() {
    m_open = false;
}

static const char* newListPopupID = "New List";
static const char* editListPopupID = "Edit List";

const char* ListPrompt::GetPopupID() {
    if (m_contextData.listIndex < 0)
        return newListPopupID;
    
    return editListPopupID;
}

void ListPrompt::DrawImpl() {
    ImGui::InputText("Name", m_data.name.data(), m_data.name.size());
}

void ListPrompt::OpenImpl() {
    m_data.name.resize(255);
}