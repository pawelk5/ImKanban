#include <gtest/gtest.h>
#include "Subtask.hpp"

/// Test suite for Subtask class
class SubtaskTest : public testing::Test
{
protected:
    Subtask t_subtask;

    /// Constructor that initializes the subtask with default values
    SubtaskTest()
        : t_subtask("default", false) { ; }

    /// Setup function to initialize data before every test
    void SetUp() override
    {
        t_subtask = Subtask("test", false);
    }
};

/// Test for Subtask constructor
/// Verifies if constructor initializes title and completion status properly
TEST_F(SubtaskTest, Constructor)
{
    Subtask subtask("example", true);
    EXPECT_EQ(subtask.GetTitle(), "example");
    EXPECT_TRUE(subtask.IsCompleted());
}

/// Test for GetTitle function
/// Verifies that GetTitle returns the correct title
TEST_F(SubtaskTest, GetTitle)
{
    EXPECT_EQ(t_subtask.GetTitle(), "test");
}

/// Test for SetTitle function
/// Verifies that SetTitle updates the title correctly
TEST_F(SubtaskTest, SetTitle)
{
    t_subtask.SetTitle("new title");
    EXPECT_EQ(t_subtask.GetTitle(), "new title");
}

/// Test for IsCompleted function
/// Verifies that IsCompleted returns the correct completion status
TEST_F(SubtaskTest, IsCompleted)
{
    EXPECT_FALSE(t_subtask.IsCompleted());
}

/// Test for SetCompleted function
/// Verifies that SetCompleted updates the completion status correctly
TEST_F(SubtaskTest, SetCompleted)
{
    t_subtask.SetCompleted(true);
    EXPECT_TRUE(t_subtask.IsCompleted());
}