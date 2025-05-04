#include "pch.h"
#include "List.hpp"
#include <imgui.h>
#include "ListPrompt.hpp"

ListPrompt::ListPrompt() 
    :m_open(false)
{

}

static constexpr int promptFlags = 
      ImGuiWindowFlags_NoMove
    | ImGuiWindowFlags_NoResize
    | ImGuiWindowFlags_AlwaysAutoResize;

static const char* popupID = "New List";

void ListPrompt::Draw(const std::function<void(const List::Data&)>& onSubmit) {
    if (!IsOpen())
        return;
    
    ImGui::OpenPopup(popupID);
        
    if (ImGui::BeginPopupModal(popupID, nullptr, promptFlags)) {
        ImGui::InputText("Name", m_data.name.data(), m_data.name.size());
        
        ImGui::Spacing();
        
        if (ImGui::Button("OK")){
            onSubmit(m_data);
            ClosePopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            ClosePopup();

        ImGui::EndPopup();
    }
}

void ListPrompt::Open(const std::optional<List::Data>& data) {
    if (data)
        m_data = *data;
    else
        m_data = {};

    m_data.name.resize(255);
    m_open = true;
}

bool ListPrompt::IsOpen() {
    return m_open;
}

void ListPrompt::ClosePopup() {
    m_open = false;
    ImGui::CloseCurrentPopup();
}