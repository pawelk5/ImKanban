#pragma once
#include "PromptBase.hpp"

template <typename InputData, typename ContextData>
class InputPrompt : public PromptBase<InputData, ContextData> {
public:
    void Draw(const std::function<void(const InputData&)>& onSubmit) {
        if (!this->IsOpen())
            return;
        
        ImGui::OpenPopup(this->GetPopupID());
            
        if (ImGui::BeginPopupModal(this->GetPopupID(), nullptr, promptFlags)) {
            // place for specific inputs
            this->DrawImpl();
                
            ImGui::Spacing();
                
            if (ImGui::Button("OK")){
                onSubmit(this->m_data);
                this->ClosePopup();
            }
        
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
                this->ClosePopup();
        }
        ImGui::EndPopup();
    }

private:
    static constexpr int promptFlags = 
          ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_AlwaysAutoResize;
};