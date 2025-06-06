#include "JsonManager.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

bool JsonManager::SaveBoardToFile(const Board &board, const std::string &filepath)
{
    try
    {
        nlohmann::json j = board.exportBoard();

        std::ofstream file(filepath);
        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file for writing: " << filepath << std::endl;
            return false;
        }

        file << j.dump(4); // Pretty print with 4 spaces indentation
        file.close();

        std::cout << "Board saved successfully to: " << filepath << std::endl;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving board to file: " << e.what() << std::endl;
        return false;
    }
}

Board JsonManager::LoadBoardFromFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file for reading: " + filepath);
    }

    nlohmann::json j;
    try
    {
        file >> j;
        file.close();

        if (!ValidateBoardJson(j))
        {
            throw std::runtime_error("Invalid board JSON structure in file: " + filepath);
        }

        Board board = Board::importBoard(j);
        std::cout << "Board loaded successfully from: " << filepath << std::endl;
        return board;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        throw std::runtime_error("JSON parse error in file " + filepath + ": " + e.what());
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error loading board from file " + filepath + ": " + e.what());
    }
}

std::string JsonManager::BoardToJsonString(const Board &board)
{
    try
    {
        nlohmann::json j = board.exportBoard();
        return j.dump(4);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error converting board to JSON string: " + std::string(e.what()));
    }
}

Board JsonManager::BoardFromJsonString(const std::string &jsonString)
{
    try
    {
        nlohmann::json j = nlohmann::json::parse(jsonString);

        if (!ValidateBoardJson(j))
        {
            throw std::runtime_error("Invalid board JSON structure");
        }

        return Board::importBoard(j);
    }
    catch (const nlohmann::json::parse_error &e)
    {
        throw std::runtime_error("JSON parse error: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error creating board from JSON string: " + std::string(e.what()));
    }
}

bool JsonManager::ValidateBoardJson(const nlohmann::json &j)
{
    try
    {
        // Check if required fields exist
        if (!j.contains("data") || !j.contains("lists"))
        {
            return false;
        }

        // Validate board data
        const auto &boardData = j.at("data");
        if (!boardData.contains("name") || !boardData.contains("filename"))
        {
            return false;
        }

        // Validate lists array
        const auto &lists = j.at("lists");
        if (!lists.is_array())
        {
            return false;
        }

        // Validate each list
        for (const auto &list : lists)
        {
            if (!list.contains("data") || !list.contains("cards"))
            {
                return false;
            }

            // Validate list data
            const auto &listData = list.at("data");
            if (!listData.contains("name"))
            {
                return false;
            }

            // Validate cards array
            const auto &cards = list.at("cards");
            if (!cards.is_array())
            {
                return false;
            }

            // Validate each card
            for (const auto &card : cards)
            {
                if (!card.contains("data") || !card.contains("subtasks"))
                {
                    return false;
                }

                // Validate card data
                const auto &cardData = card.at("data");
                if (!cardData.contains("title") || !cardData.contains("description") || !cardData.contains("isCompleted"))
                {
                    return false;
                }

                // Validate subtasks array
                const auto &subtasks = card.at("subtasks");
                if (!subtasks.is_array())
                {
                    return false;
                }

                // Validate each subtask
                for (const auto &subtask : subtasks)
                {
                    if (!subtask.contains("title") || !subtask.contains("isCompleted"))
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }
    catch (...)
    {
        return false;
    }
}
