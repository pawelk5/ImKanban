#pragma once
#include "api.h"
#include "ContainerBase.hpp"
#include "Subtask.hpp"
#include <string>

/// Data held by a card
struct CardData
{
    std::string title;       ///< Title of the card
    std::string description; ///< Description of the card
    bool isCompleted;        ///< Completion status of the card
};

/// Represents a card containing a list of subtasks
class EXPORT_API Card : public ContainerBase<Subtask, CardData>
{
public:
    /// Constructs a card
    /// \param data Data to be stored in the card
    explicit Card(const CardData &data)
        : ContainerBase(data) {}

    /// Constructs a card without specifying completion status
    /// \param title Title of the card
    /// \param description Description of the card
    Card(const std::string &title, const std::string &description)
        : ContainerBase({title, description, false}) {}

    /// Returns a copy of stored card data
    /// \return Copy of stored card data
    CardData GetCardData() const
    {
        return GetData();
    }

    /// Returns a const reference to stored card data
    /// \return Const reference to stored card data
    const CardData &GetCardDataRef() const
    {
        return GetDataRef();
    }

    /// Updates the card's data
    /// \param data New data to store in the card
    void UpdateCardData(const CardData &data)
    {
        Update(data);
    }

    /// Counts completed subtasks from the card
    int CountCompletedSubtasks()
    {
        int completedCount = 0;
        for (const auto &subtask : GetElementArray())
        {
            if (subtask->IsCompleted())
                ++completedCount;
        }
        return completedCount;
    }

    /// Marks the card as completed if all subtasks are completed
    void UpdateCompletionStatus()
    {
        if (GetElementArray().empty())
            return;

        bool allCompleted = true;
        for (const auto &subtask : GetElementArray())
        {
            if (!subtask->IsCompleted())
            {
                allCompleted = false;
                break;
            }
        }
        m_data.isCompleted = allCompleted;
    }

    /// Sets the completion status of the card
    /// \param isCompleted New completion status
    void SetCompletionStatus(bool isCompleted)
    {
        m_data.isCompleted = isCompleted;
    }
};