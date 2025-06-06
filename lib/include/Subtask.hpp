#pragma once
#include <string>
#include <nlohmann/json.hpp>

struct SubtaskData
{
    std::string title;
    bool isCompleted = false;

    /// Exports SubtaskData to JSON
    nlohmann::json exportBoard() const;

    /// Imports SubtaskData from JSON
    static SubtaskData importBoard(const nlohmann::json &j);
};

/// Represents a subtask with a title and completion status
class Subtask
{
public:
    /// Constructs a subtask
    /// \param title Title of the subtask
    /// \param isCompleted Completion status of the subtask (default: false)
    Subtask(const std::string &title, bool isCompleted = false)
        : m_title(title), m_isCompleted(isCompleted) {}

    /// Constructs a subtask with only a title
    /// \param title Title of the subtask
    Subtask(const std::string &title)
        : m_title(title), m_isCompleted(false) {}

    /// Constructs a subtask from SubtaskData
    /// \param data SubtaskData containing title and completion status
    Subtask(const SubtaskData &data)
        : m_title(data.title), m_isCompleted(data.isCompleted) {}

    /// Gets the title of the subtask
    /// \return Title of the subtask
    const std::string &GetTitle() const
    {
        return m_title;
    }

    /// Sets the title of the subtask
    /// \param title New title for the subtask
    void SetTitle(const std::string &title)
    {
        m_title = title;
    }

    /// Checks if the subtask is completed
    /// \return True if the subtask is completed, false otherwise
    bool IsCompleted() const
    {
        return m_isCompleted;
    }

    /// Sets the completion status of the subtask
    /// \param isCompleted New completion status
    void SetCompleted(bool isCompleted)
    {
        m_isCompleted = isCompleted;
    }

    SubtaskData GetData() const
    {
        return {m_title, m_isCompleted};
    }

    /// Exports Subtask to JSON
    nlohmann::json exportBoard() const;

    /// Imports Subtask from JSON
    static Subtask importBoard(const nlohmann::json &j);

public:
    /// Title of the subtask
    std::string m_title;

    /// Completion status of the subtask
    bool m_isCompleted;
};