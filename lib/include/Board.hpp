#pragma once
#include "ContainerBase.hpp"
#include "api.h"
#include <nlohmann/json.hpp>
#include <memory>

#include "List.hpp"

/// Data of the board
struct EXPORT_API BoardData
{
    std::string name;
    std::string filename;

    /// Exports BoardData to JSON
    nlohmann::json exportBoard() const;

    /// Imports BoardData from JSON
    static BoardData importBoard(const nlohmann::json &j);
};

/// Board class representing a single board
class EXPORT_API Board : public ContainerBase<List, BoardData>
{
public:
    /// Index to a card or a list
    struct ItemIndex
    {
        int list = -1;

        /// (TODO: change to std::optional)
        int card = -1;
        int subtask = -1;
    };

    /// Type alias for moving items
    using MoveData = ItemIndex;

public:
    /// Inherited constructor, additionally creates pre-defined lists
    /// \param data data of the board
    explicit Board(const BoardData &data) : ContainerBase<List, BoardData>(data)
    {
        CreateBasicLists();
    }

    /// Constructor that tries to load from file, creates new board if file doesn't exist
    /// \param filename The filename to load from (or create new board with this filename)
    explicit Board(const std::string &filename);

    /// Moves a card to another location
    /// \param source position of the element to be moved
    /// \param destination target position where the element should be moved
    /// \warning if destination.card is -1 or equal to the size of target list, the element will be placed at the end
    /// \throws std::out_of_range if source or destination are invalid
    void MoveCard(
        const MoveData &source,
        const MoveData &destination);

    /// Moves a list to another location
    /// \param source the current position of the element to be moved
    /// \param destination the target position where the element will be moved
    /// \warning if destination is -1, the element will be placed at the end
    /// \throws std::out_of_range if source or destination are invalid
    void MoveList(
        const int &source,
        const int &destination);

    /// Exports Board to JSON
    nlohmann::json exportBoard() const;

    /// Imports Board from JSON
    static Board importBoard(const nlohmann::json &j);

    /// Automatically saves board to .dat directory based on filename
    /// \return true if successful, false otherwise
    bool saveToFile() const;

    /// Automatically loads board from .dat directory based on filename
    /// \param filename The filename to load (without .json extension)
    /// \return Board loaded from file, or nullptr if file doesn't exist
    static std::unique_ptr<Board> loadFromFile(const std::string &filename);

    /// Gets the full file path for a board filename
    /// \param filename The board filename (without extension)
    /// \return Full path to the board file in .dat directory
    static std::string getBoardFilePath(const std::string &filename);

    /// Enables or disables automatic saving to file
    /// \param enabled true to enable auto-save, false to disable
    void setAutoSave(bool enabled) { m_autoSave = enabled; }

    /// Gets the auto-save status
    /// \return true if auto-save is enabled, false otherwise
    bool isAutoSaveEnabled() const { return m_autoSave; }

    /// Gets the filename of the board
    /// \return The filename of the board
    std::string getFilename() const
    {
        if (m_data.filename.empty())
        {
            return "json_" + m_data.name;
        }
        return m_data.filename;
    }

private:
    /// Creates pre-defined lists
    void CreateBasicLists();

    /// Automatically saves board if auto-save is enabled
    void autoSave() const;

    /// Auto-save flag
    bool m_autoSave = true;

    /// Generates a random filename based on the given title
    /// \param title The base title for the filename
    /// \return A filename in the format "title<random_number>.json"

public:
    static std::string generateNewFilename(const std::string &title)
    {
        return title + std::to_string(rand()) + ".json";
    }
};