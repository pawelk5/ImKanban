#include "Subtask.hpp"

nlohmann::json SubtaskData::exportBoard() const
{
    nlohmann::json j;
    j["title"] = title;
    j["isCompleted"] = isCompleted;
    return j;
}

SubtaskData SubtaskData::importBoard(const nlohmann::json &j)
{
    SubtaskData data;
    data.title = j.at("title").get<std::string>();
    data.isCompleted = j.at("isCompleted").get<bool>();
    return data;
}

nlohmann::json Subtask::exportBoard() const
{
    nlohmann::json j;
    j["title"] = m_title;
    j["isCompleted"] = m_isCompleted;
    return j;
}

Subtask Subtask::importBoard(const nlohmann::json &j)
{
    std::string title = j.at("title").get<std::string>();
    bool isCompleted = j.at("isCompleted").get<bool>();
    return Subtask(title, isCompleted);
}
