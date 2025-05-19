#include "FullCardView.hpp"
#include "Board.hpp" // Replace with the actual header file that defines the Board namespace

// No additional constructor logic needed, but we must define it
FullCardView::FullCardView(
    std::function<void(Board::ItemIndex, std::optional<SubtaskData>)> m_open_subtask_prompt)
    : m_open_subtask_prompt(m_open_subtask_prompt)
{
    m_open = false;
}

void FullCardView::DrawImpl()
{
    ImGui::Text("Card Details");
    ImGui::Separator();
    auto data = m_data.selectedCard;
    auto cardData = data->GetCardData();

    ImGui::Text("Title: %s", cardData.title.c_str());
    ImGui::Text("Description: %s", cardData.description.c_str());
    ImGui::Text("Completed: %s", cardData.isCompleted ? "Yes" : "No");
    ImGui::Text("Subtasks: %d/%d", data->CountCompletedSubtasks(),
                data->GetElementArray().size());
    ImGui::Separator();
    ImGui::Text("Subtasks:");
    ImGui::SameLine();
    if (ImGui::Button("Add"))
    {
        m_open_subtask_prompt(
            Board::ItemIndex{m_contextData.list, m_contextData.card, -1},
            std::optional<SubtaskData>(std::nullopt));
    }
    for (auto it = data->GetElementArray().begin(); it < data->GetElementArray().end(); ++it)
    {
        ImGui::Text(" - %s: %s", (*it)->GetTitle().c_str(),
                    (*it)->IsCompleted() ? "Completed" : "Not Completed");
        ImGui::SameLine();
        if (ImGui::Button(("Edit##" + std::to_string(data->AsIndex(it))).c_str()))
        {
            m_open_subtask_prompt(
                Board::ItemIndex{m_contextData.list, m_contextData.card,
                                 data->AsIndex(it)},
                std::optional<SubtaskData>((*it)->GetData()));
        }
    }
}