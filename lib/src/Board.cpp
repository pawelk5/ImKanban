#include "Board.hpp"
#include "List.hpp"
#include "JsonManager.hpp"
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>

void Board::CreateBasicLists()
{
    std::array<std::string, 3> baseListNames{
        "To Do",
        "In Progress",
        "Done"};
    m_array.reserve(baseListNames.size());

    for (const auto &name : baseListNames)
        AddElement(List(ListData{name}));
}

void Board::MoveCard(
    const MoveData &source,
    const MoveData &destination)
{
    if (!IsValid(source.list))
        throw std::out_of_range(invalidIndex);
    if (!IsValid(destination.list))
        throw std::out_of_range(invalidIndex);

    auto &sourceList = At(source.list);
    auto &destinationList = At(destination.list);

    auto sourceCard = sourceList->At(source.card);

    sourceList->RemoveElement(source.card);

    if (destination.card == -1)
        destinationList->AddElement(sourceCard);
    else
        destinationList->InsertElement(sourceCard, destination.card);

    // Auto-save after moving card
    autoSave();
}

void Board::MoveList(
    const int &source,
    const int &destination)
{

    if (!IsValid(source))
        throw std::out_of_range(invalidIndex);
    if (!IsValid(destination) && destination != -1)
        throw std::out_of_range(invalidIndex);

    auto sourceList = At(source);

    RemoveElement(source);

    if (destination == -1)
        AddElement(sourceList);
    else
        InsertElement(sourceList, destination);

    // Auto-save after moving list
    autoSave();
}

nlohmann::json BoardData::exportBoard() const
{
    nlohmann::json j;
    j["name"] = name;
    j["filename"] = filename;
    return j;
}

BoardData BoardData::importBoard(const nlohmann::json &j)
{
    BoardData data;
    data.name = j.at("name").get<std::string>();
    data.filename = j.at("filename").get<std::string>();
    return data;
}

nlohmann::json Board::exportBoard() const
{
    nlohmann::json j;

    // Save board data
    j["data"] = GetDataRef().exportBoard();

    // Save lists
    nlohmann::json listsArray = nlohmann::json::array();
    for (const auto &list : GetElementArray())
    {
        listsArray.push_back(list->exportBoard());
    }
    j["lists"] = listsArray;

    return j;
}

Board Board::importBoard(const nlohmann::json &j)
{
    // Create board with data
    BoardData boardData = BoardData::importBoard(j.at("data"));
    Board board(boardData);

    // Clear default lists first
    board.m_array.clear();

    // Load lists
    if (j.contains("lists"))
    {
        for (const auto &listJson : j.at("lists"))
        {
            List list = List::importBoard(listJson);
            board.AddElement(list);
        }
    }

    return board;
}

bool Board::saveToFile() const
{
    if (getFilename().empty())
    {
        std::cerr << "Error: Board filename is empty, cannot save to file" << std::endl;
        return false;
    }

    std::string filepath = getBoardFilePath(getFilename());
    return JsonManager::SaveBoardToFile(*this, filepath);
}

std::unique_ptr<Board> Board::loadFromFile(const std::string &filename)
{
    std::string filepath = getBoardFilePath(filename);

    // Check if file exists
    std::ifstream file(filepath);
    if (!file.good())
    {
        std::cout << "Board file does not exist: " << filepath << std::endl;
        return nullptr;
    }
    file.close();

    try
    {
        Board board = JsonManager::LoadBoardFromFile(filepath);
        return std::make_unique<Board>(std::move(board));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading board from file: " << e.what() << std::endl;
        return nullptr;
    }
}

std::string Board::getBoardFilePath(const std::string &filename)
{
    // Create .dat directory if it doesn't exist
    std::filesystem::create_directories("data");

    // Add .json extension if not present
    std::string fullFilename = filename;
    if (fullFilename.find(".json") == std::string::npos)
    {
        fullFilename += ".json";
    }

    return "../../data/" + fullFilename;
}

void Board::autoSave() const
{
    if (m_autoSave && !m_data.filename.empty())
    {
        saveToFile();
    }
}

Board::Board(const std::string &filename) : ContainerBase<List, BoardData>({filename, filename})
{

    std::cout << "Initializing Board with filename: " << filename << std::endl;
    // Try to load from file first
    auto existingBoard = loadFromFile(filename);
    if (existingBoard)
    {
        // If file exists, copy the data and lists from the loaded board
        m_data = existingBoard->m_data;
        m_array = std::move(existingBoard->m_array);
        std::cout << "Loaded existing board from file: " << filename << std::endl;
    }
    else
    {
        // If file doesn't exist, create new board with basic lists
        CreateBasicLists();
        std::cout << "Created new board: " << filename << std::endl;
    }
}