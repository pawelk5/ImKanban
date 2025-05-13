#include "pch.h"
#include "SubtaskPrompt.hpp"

SubtaskPrompt::SubtaskPrompt()
{
    m_open = false;
}

const char *SubtaskPrompt::GetPopupID()
{

    if (m_contextData.card < 0)
        return defs::Labels::newCardPopup;

    return defs::Labels::editCardPopup;
}

void SubtaskPrompt::DrawImpl()
{
    ImGui::InputText("Title", m_data.title.data(), m_data.title.size());
    ImGui::Checkbox("Completed", &m_data.isCompleted);
}

void SubtaskPrompt::OpenImpl()
{
    m_data.title.resize(255);
}
