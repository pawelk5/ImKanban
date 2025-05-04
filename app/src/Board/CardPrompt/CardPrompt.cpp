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

static const char* popupID = "New Task";

void CardPrompt::Draw(const std::function<void(const Card&)>& onSubmit) {
    if (!IsOpen())
        return;
    
    ImGui::OpenPopup(popupID);
        
    if (ImGui::BeginPopupModal(popupID, nullptr, promptFlags)) {
        ImGui::InputText("Name", m_cardData.title.data(), m_cardData.title.size());
        
        ImGui::Spacing();
        
        if (ImGui::Button("OK")){
            // TODO: check if card title is empty
            Card newCard(m_cardData.title);
            onSubmit(newCard);
            ClosePopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            ClosePopup();

        ImGui::EndPopup();
    }
}

void CardPrompt::Open(uint32_t index) {
    m_cardData.title.clear();
    m_cardData.title.resize(255);
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