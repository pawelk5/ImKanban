#include "pch.h"
#include "List.hpp"
#include <imgui.h>
#include "CardPrompt.hpp"

CardPrompt::CardPrompt() 
    :m_open(false), m_index(-1)
{

}

static constexpr int promptFlags = 
      ImGuiWindowFlags_NoMove
    | ImGuiWindowFlags_NoResize
    | ImGuiWindowFlags_AlwaysAutoResize;

static const char* popupID = "CardPrompt";

void CardPrompt::Draw(const std::function<void(const Card::Data&)>& onSubmit) {
    if (!IsOpen())
        return;
    
    ImGui::OpenPopup(popupID);
        
    if (ImGui::BeginPopupModal(popupID, nullptr, promptFlags)) {
        ImGui::InputText("Name", m_data.title.data(), m_data.title.size());
        
        ImGui::Spacing();
        
        if (ImGui::Button("OK")){
            // TODO: check if card title is empty
            onSubmit(m_data);
            ClosePopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            ClosePopup();

        ImGui::EndPopup();
    }
}

void CardPrompt::Open(const std::optional<Card::Data>& data, uint32_t index) {
    if (data)
        m_data = *data;
    else
        m_data = {};

    m_data.title.resize(255);

    m_open = true;
    m_index = index;
}

bool CardPrompt::IsOpen() {
    return m_open;
}

uint32_t CardPrompt::GetIndex() {
    return m_index;
}

void CardPrompt::ClosePopup() {
    m_open = false;
    ImGui::CloseCurrentPopup();
}