#include <gtest/gtest.h>
#include "Card.hpp"

/// Test suite for Card class
class CardTest : public testing::Test
{
protected:
    CardData t_data;
    Card t_card;

    /// Constructor that initializes the card with default data
    CardTest()
        : t_card(t_data) {}

    /// Setup function to initialize data before every test
    void SetUp() override
    {
        t_data.title = "test";
        t_card = Card(t_data);
    }
};

/// Test for Card constructor
/// Verifies if constructor stores data properly
TEST_F(CardTest, BaseConstructor)
{
    {
        CardData testData;
        testData.title = "test2";
        Card card2(testData);
        EXPECT_EQ(card2.GetDataRef().title, "test2");
    }
}

/// Test for GetData function
/// Verifies that GetData returns a copy of stored data
TEST_F(CardTest, GetData)
{
    auto data = t_card.GetData();
    EXPECT_EQ(data.title, "test");

    data.title = "changed";
    EXPECT_EQ(t_card.GetData().title, "test");
}

/// Test for Update function
/// Verifies that Update changes stored data
TEST_F(CardTest, Update)
{
    auto data = t_card.GetData();

    data.title = "changed";
    t_card.Update(data);
    EXPECT_EQ(t_card.GetDataRef().title, "changed");
}

/// Test for adding subtasks to the card
/// Verifies that subtasks are added correctly
TEST_F(CardTest, AddSubtask)
{
    Subtask subtask1("Subtask 1", false);
    Subtask subtask2("Subtask 2", true);

    t_card.AddElement(subtask1);
    t_card.AddElement(subtask2);

    EXPECT_EQ(t_card.GetElementArray().size(), 2);
    EXPECT_EQ(t_card.GetElementArray()[0]->GetTitle(), "Subtask 1");
    EXPECT_EQ(t_card.GetElementArray()[1]->GetTitle(), "Subtask 2");
}

/// Test for removing subtasks from the card
/// Verifies that subtasks are removed correctly
TEST_F(CardTest, RemoveSubtask)
{
    Subtask subtask1("Subtask 1", false);
    Subtask subtask2("Subtask 2", true);

    t_card.AddElement(subtask1);
    t_card.AddElement(subtask2);

    auto it = t_card.GetElementArray().begin();
    t_card.RemoveElement(it);

    EXPECT_EQ(t_card.GetElementArray().size(), 1);
    EXPECT_EQ(t_card.GetElementArray()[0]->GetTitle(), "Subtask 2");
}

/// Test for updating the card's completion status
/// Verifies that the card is marked as completed only if all subtasks are completed
TEST_F(CardTest, UpdateCompletionStatus)
{
    Subtask subtask1("Subtask 1", true);
    Subtask subtask2("Subtask 2", false);

    t_card.AddElement(subtask1);
    t_card.AddElement(subtask2);

    t_card.UpdateCompletionStatus();
    EXPECT_FALSE(t_card.GetCardDataRef().isCompleted);

    t_card.GetElementArray()[1]->SetCompleted(true);
    t_card.UpdateCompletionStatus();
    EXPECT_TRUE(t_card.GetCardDataRef().isCompleted);
}

/// Test for clearing all subtasks
/// Verifies that all subtasks can be removed from the card
TEST_F(CardTest, ClearSubtasks)
{
    Subtask subtask1("Subtask 1", false);
    Subtask subtask2("Subtask 2", true);

    t_card.AddElement(subtask1);
    t_card.AddElement(subtask2);

    while (!t_card.GetElementArray().empty())
    {
        t_card.RemoveElement(t_card.GetElementArray().begin());
    }

    EXPECT_TRUE(t_card.GetElementArray().empty());
}

/// Test for updating card data while keeping subtasks intact
/// Verifies that updating card metadata does not affect subtasks
TEST_F(CardTest, UpdateCardDataKeepsSubtasks)
{
    Subtask subtask1("Subtask 1", false);
    Subtask subtask2("Subtask 2", true);

    t_card.AddElement(subtask1);
    t_card.AddElement(subtask2);

    CardData newData = t_card.GetCardData();
    newData.title = "Updated Title";
    t_card.UpdateCardData(newData);

    EXPECT_EQ(t_card.GetCardDataRef().title, "Updated Title");
    EXPECT_EQ(t_card.GetElementArray().size(), 2);
    EXPECT_EQ(t_card.GetElementArray()[0]->GetTitle(), "Subtask 1");
    EXPECT_EQ(t_card.GetElementArray()[1]->GetTitle(), "Subtask 2");
}

/// Test for manually setting the completion status
/// Verifies that SetCompletionStatus updates the isCompleted field
TEST_F(CardTest, SetCompletionStatus)
{
    // Initially, the card is not completed
    EXPECT_FALSE(t_card.GetCardDataRef().isCompleted);

    // Manually set the card as completed
    t_card.SetCompletionStatus(true);
    EXPECT_TRUE(t_card.GetCardDataRef().isCompleted);

    // Manually set the card as not completed
    t_card.SetCompletionStatus(false);
    EXPECT_FALSE(t_card.GetCardDataRef().isCompleted);
}

/// Test for updating the card's completion status with no subtasks
/// Verifies that a card with no subtasks requires manual completion
TEST_F(CardTest, UpdateCompletionStatusNoSubtasks)
{
    // Ensure the card starts with no subtasks
    EXPECT_TRUE(t_card.GetElementArray().empty());

    // Update completion status
    t_card.UpdateCompletionStatus();

    // Verify that the card is not marked as completed
    EXPECT_FALSE(t_card.GetCardDataRef().isCompleted);

    // Manually mark the card as completed
    t_card.SetCompletionStatus(true);
    EXPECT_TRUE(t_card.GetCardDataRef().isCompleted);
}

/// Test for updating the card's completion status with subtasks
/// Verifies that the card is marked as completed only if all subtasks are completed
TEST_F(CardTest, UpdateCompletionStatusWithSubtasks)
{
    Subtask subtask1("Subtask 1", true);
    Subtask subtask2("Subtask 2", false);

    t_card.AddElement(subtask1);
    t_card.AddElement(subtask2);

    // Update completion status
    t_card.UpdateCompletionStatus();
    EXPECT_FALSE(t_card.GetCardDataRef().isCompleted);

    // Mark the second subtask as completed
    t_card.GetElementArray()[1]->SetCompleted(true);
    t_card.UpdateCompletionStatus();
    EXPECT_TRUE(t_card.GetCardDataRef().isCompleted);
}