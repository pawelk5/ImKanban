#pragma once

template<typename TData, typename PromptData>
class PromptBase {
public:
    void Draw(const std::function<void(const TData&)>& onSubmit) {
        if (!IsOpen())
            return;
        
        ImGui::OpenPopup(GetPopupID());
            
        if (ImGui::BeginPopupModal(GetPopupID(), nullptr, promptFlags)) {
            // place for specific inputs
            DrawImpl();
            
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
    
    void Open(const std::optional<TData>& data, const PromptData& promptData) {
        if (data)
            m_data = *data;
        else
            m_data = {};
        m_promptData = promptData;
        m_open = true;
    
        OpenImpl();
    }

    bool IsOpen() {
        return m_open;
    }
    
    const PromptData& GetPromptData() {
        return m_promptData;
    }
    
protected:
    bool m_open;
    PromptData m_promptData;
    
    TData m_data;
    
protected:
    PromptBase() = default;

    virtual void DrawImpl() = 0;
    virtual void OpenImpl() = 0;
    virtual const char* GetPopupID() = 0;

private:
    void ClosePopup() {
        m_open = false;
        ImGui::CloseCurrentPopup();
    }

private:
    static constexpr int promptFlags = 
          ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_AlwaysAutoResize;
};