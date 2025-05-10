#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "Board.hpp"
#include "List.hpp"

static const char* inProgressLabel = "In Progress";
static const char* toDoLabel = "To Do";
static const char* doneLabel = "Done";

/// Test suite for Board class
class BoardTest : public testing::Test {
protected:
    BoardData t_data;
    Board t_board;

    /// Constructor that initializes the board with empty data
    BoardTest() 
        : t_board(t_data) { ; }
    
    /// Setup function to initialize data before every test
    void SetUp() override {
        t_data.name = "test";
        t_board = Board(t_data);
    }
};

/// Test for Board constructor
/// Verifies if constructor creates predefined lists
TEST_F(BoardTest, BaseConstructor)
{
    {
        BoardData data {"test2"};
        Board board(data);
        const auto &lists = board.GetElementArray();
        EXPECT_EQ(lists.size(), 3);
        for (const auto &list : lists)
            EXPECT_EQ(list->GetElementArray().size(), 0);
    }
}

/// Test for moving cards between lists
TEST_F(BoardTest, MoveCard)
{
    const auto &lists = t_board.GetElementArray();
    t_board.RemoveElement(lists.end() - 1);


    t_board.At(0)->AddElement(Card({"TestCard"}));
    EXPECT_EQ(t_board.At(0)->GetElementArray().size(), 1);
    EXPECT_EQ(t_board.At(1)->GetElementArray().size(), 0);
    // move same card to {1,0}
    t_board.MoveCard(
        {0, 0}, {1, 0});

    EXPECT_EQ(t_board.At(0)->GetElementArray().size(), 0);
    EXPECT_EQ(t_board.At(1)->GetElementArray().size(), 1);
    EXPECT_EQ(t_board.At(1)->At(0)->GetData().title, "TestCard");

    // move the same card back to {0,0}
    t_board.MoveCard(
        {1, 0},
        {0, 0});

    EXPECT_EQ(t_board.At(0)->GetElementArray().size(), 1);
    EXPECT_EQ(t_board.At(1)->GetElementArray().size(), 0);
    EXPECT_EQ(t_board.At(0)->At(0)->GetData().title, "TestCard");
}

/// Test for handling errors during card movement
TEST_F(BoardTest, MoveCardErrors)
{
    auto &lists = t_board.GetElementArray();

    // invalid card source index
    EXPECT_THROW(
        t_board.MoveCard(
            {0, 0}, {1, 0});
            , std::out_of_range);
    
    // invalid source list index
    EXPECT_THROW(
        t_board.MoveCard(
            {3, 0},
            {1, 0});
        , std::out_of_range);
    
    // invalid card destination index
    t_board.At(0)->AddElement(Card( {"testcard"} ));
    EXPECT_THROW(
        t_board.MoveCard(
            {0, 0}, {1, 1});
            , std::out_of_range);
    
    // invalid destination list index
    EXPECT_THROW(
        t_board.MoveCard(
            {0, 0}, {3, 0});
            , std::out_of_range);
}

/// Test for moving lists
TEST_F(BoardTest, MoveList)
{
    const auto &lists = t_board.GetElementArray();

    t_board.At(0)->AddElement(Card({"TestCard"}));
    t_board.At(2)->AddElement(Card({"TestCard2"}));
    t_board.At(2)->AddElement(Card({"TestCard3"}));

    EXPECT_EQ(t_board.At(0)->GetElementArray().size(), 1);
    EXPECT_EQ(t_board.At(1)->GetElementArray().size(), 0);
    // move same list to index = 1
    t_board.MoveList(0, 1);

    EXPECT_EQ(t_board.GetElementArray().size(), 3);

    // check labels
    EXPECT_EQ(t_board.At(0)->GetDataRef().name, inProgressLabel);
    EXPECT_EQ(t_board.At(1)->GetDataRef().name, toDoLabel);
    EXPECT_EQ(t_board.At(2)->GetDataRef().name, doneLabel);

    // check cards
    EXPECT_EQ(t_board.At(0)->GetElementArray().size(), 0);
    EXPECT_EQ(t_board.At(1)->GetElementArray().size(), 1);
    EXPECT_EQ(t_board.At(1)->At(0)->GetData().title, "TestCard");
    EXPECT_EQ(t_board.At(2)->GetElementArray().size(), 2);

    // move the same list back to index = 0
    t_board.MoveList(1, 0);

    EXPECT_EQ(t_board.GetElementArray().size(), 3);

    // check cards
    EXPECT_EQ(t_board.At(0)->GetElementArray().size(), 1);
    EXPECT_EQ(t_board.At(0)->At(0)->GetData().title, "TestCard");
    EXPECT_EQ(t_board.At(1)->GetElementArray().size(), 0);
    EXPECT_EQ(t_board.At(2)->GetElementArray().size(), 2);

    // check labels
    EXPECT_EQ(t_board.At(0)->GetDataRef().name, toDoLabel);
    EXPECT_EQ(t_board.At(1)->GetDataRef().name, inProgressLabel);
    EXPECT_EQ(t_board.At(2)->GetDataRef().name, doneLabel);
}

/// Test for handling errors during list movement
TEST_F(BoardTest, MoveListErrors)
{
    auto &lists = t_board.GetElementArray();

    // invalid list source index
    EXPECT_THROW(
        t_board.MoveList(-1, 0);
            , std::out_of_range);
    
    // invalid list source index (upper bound)
    EXPECT_THROW(
        t_board.MoveList(3, 0);
        , std::out_of_range);
    
    // invalid destination list index
    EXPECT_THROW(
        t_board.MoveList(0, -2);
            , std::out_of_range);

    // invalid destination list index (upper bound)
    EXPECT_THROW(
        t_board.MoveList(0, 3);
            , std::out_of_range);
}