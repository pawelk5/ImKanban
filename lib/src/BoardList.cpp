#include "BoardList.hpp"
#include "Board.hpp"
#include <exception>
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

const char *boardKey = "boards";
const char *titleKey = "title";
const char *filenameKey = "filename";

BoardList::~BoardList()
{
    SaveToFile();
}

void BoardList::SaveToFile()
{
    using namespace nlohmann;
    if (m_data.filepath == "")
        return;

    std::ofstream file;
    file.open(m_data.filepath);

    if (!file)
        throw std::runtime_error("Couldn't open " + m_data.filepath);

    json data{};

    std::vector<json> dataStr;
    json boardObj;
    for (const auto &board : m_array)
    {
        boardObj[titleKey] = board->name;
        boardObj[filenameKey] = board->filename;

        dataStr.push_back(boardObj);
    }

    data[boardKey] = dataStr;
    file << data.dump(4);
    file.close();
}

void BoardList::LoadFromFile()
{
    using namespace nlohmann;
    if (m_data.filepath == "")
        return;

    std::ifstream file;
    file.open(m_data.filepath);

    if (!file)
        throw std::runtime_error("Couldn't open " + m_data.filepath);

    try
    {
        json data = json::parse(file);

        for (const auto &board : data["boards"])
        {
            std::string filename = board["filename"];
            std::string title = board["title"];

            if (filename.empty())
                filename = Board::generateNewFilename(title);
            AddElement(BoardData{title, filename});
        }
    }
    catch (std::exception e)
    {
        file.close();
        // if couldn't load start with empty array
        m_array = {};
        throw;
    }
    file.close();
}