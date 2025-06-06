#pragma once
#include "api.h"
#include "Board.hpp"
#include <string>
#include <nlohmann/json.hpp>

/// JsonManager class for handling JSON serialization and file I/O operations
class EXPORT_API JsonManager
{
public:
    /// Saves a board to a JSON file
    /// \param board The board to save
    /// \param filepath Path to the JSON file
    /// \return true if successful, false otherwise
    static bool SaveBoardToFile(const Board &board, const std::string &filepath);

    /// Loads a board from a JSON file
    /// \param filepath Path to the JSON file
    /// \return Board object loaded from file
    /// \throws std::runtime_error if file cannot be read or parsed
    static Board LoadBoardFromFile(const std::string &filepath);

    /// Converts a board to JSON string
    /// \param board The board to convert
    /// \return JSON string representation
    static std::string BoardToJsonString(const Board &board);

    /// Creates a board from JSON string
    /// \param jsonString JSON string representation
    /// \return Board object created from JSON
    /// \throws std::runtime_error if JSON cannot be parsed
    static Board BoardFromJsonString(const std::string &jsonString);

private:
    /// Validates JSON structure for board data
    /// \param j JSON object to validate
    /// \return true if valid, false otherwise
    static bool ValidateBoardJson(const nlohmann::json &j);
};
