#include "List.hpp"

nlohmann::json ListData::exportBoard() const
{
    nlohmann::json j;
    j["name"] = name;
    return j;
}

ListData ListData::importBoard(const nlohmann::json &j)
{
    ListData data;
    data.name = j.at("name").get<std::string>();
    return data;
}

nlohmann::json List::exportBoard() const
{
    nlohmann::json j;

    // Save list data
    j["data"] = GetDataRef().exportBoard();

    // Save cards
    nlohmann::json cardsArray = nlohmann::json::array();
    for (const auto &card : GetElementArray())
    {
        cardsArray.push_back(card->exportBoard());
    }
    j["cards"] = cardsArray;

    return j;
}

List List::importBoard(const nlohmann::json &j)
{
    // Create list with data
    ListData listData = ListData::importBoard(j.at("data"));
    List list(listData);

    // Load cards
    if (j.contains("cards"))
    {
        for (const auto &cardJson : j.at("cards"))
        {
            Card card = Card::importBoard(cardJson);
            list.AddElement(card);
        }
    }

    return list;
}
