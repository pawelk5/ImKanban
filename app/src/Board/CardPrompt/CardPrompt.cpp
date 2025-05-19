#include "Core/Utils/Constants.hpp"
#include "pch.h"
#include "CardPrompt.hpp"

CardPrompt::CardPrompt()
{
    m_open = false;
}

const char *CardPrompt::GetPopupID()
{
    if (m_contextData.card < 0)
        return Labels::newCardPopup;

    return Labels::editCardPopup;
}

void CardPrompt::DrawImpl(sf::RenderTarget &target)
{
    ImGui::InputText("##Name", m_data.title.data(), m_data.title.size());
    ImGui::InputText("Description", m_data.description.data(), m_data.description.size());
    ImGui::Checkbox("Completed", &m_data.isCompleted);

    // for (auto &subtask : m_data)
    // {
    //     ImGui::InputText("Subtask", subtask->GetTitle().data(), subtask->GetTitle().size());
    //     ImGui::Checkbox("Completed", &subtask->IsCompleted());
    // }
}

void CardPrompt::OpenImpl()
{
    m_data.title.resize(UI::maxCardNameSize);
    m_data.description.resize(UI::maxCardNameSize);
}