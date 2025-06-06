#include "Card.hpp"

nlohmann::json CardData::exportBoard() const
{
    nlohmann::json j;
    j["title"] = title;
    j["description"] = description;
    j["isCompleted"] = isCompleted;
    return j;
}

CardData CardData::importBoard(const nlohmann::json &j)
{
    CardData data;
    data.title = j.at("title").get<std::string>();
    data.description = j.at("description").get<std::string>();
    data.isCompleted = j.at("isCompleted").get<bool>();
    return data;
}

nlohmann::json Card::exportBoard() const
{
    nlohmann::json j;

    // Save card data
    j["data"] = GetDataRef().exportBoard();

    // Save subtasks
    nlohmann::json subtasksArray = nlohmann::json::array();
    for (const auto &subtask : GetElementArray())
    {
        subtasksArray.push_back(subtask->exportBoard());
    }
    j["subtasks"] = subtasksArray;

    return j;
}

Card Card::importBoard(const nlohmann::json &j)
{
    // Create card with data
    CardData cardData = CardData::importBoard(j.at("data"));
    Card card(cardData);

    // Load subtasks
    if (j.contains("subtasks"))
    {
        for (const auto &subtaskJson : j.at("subtasks"))
        {
            Subtask subtask = Subtask::importBoard(subtaskJson);
            card.AddElement(subtask);
        }
    }

    return card;
}
