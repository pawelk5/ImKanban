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

void ListPrompt::Draw(const std::function<void(const List&)>& onSubmit) {
    if (!IsOpen())
        return;
    
    ImGui::OpenPopup(popupID);
        
    if (ImGui::BeginPopupModal(popupID, nullptr, promptFlags)) {
        ImGui::InputText("Name", m_listData.name.data(), m_listData.name.size());
        
        ImGui::Spacing();
        
        if (ImGui::Button("OK")){
            List newList(m_listData.name);
            onSubmit(newList);
            ClosePopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            ClosePopup();

        ImGui::EndPopup();
    }
}

void ListPrompt::Open() {
    m_listData.name.clear();
    m_listData.name.resize(255);
    m_open = true;
}

bool ListPrompt::IsOpen() {
    return m_open;
}

void ListPrompt::ClosePopup() {
    m_open = false;
    ImGui::CloseCurrentPopup();
}