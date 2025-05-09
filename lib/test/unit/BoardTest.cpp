#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "Board.hpp"
#include "List.hpp"


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

    t_board.MoveCard(
        {0, 0}, {1, 0});

    EXPECT_EQ(t_board.At(0)->GetElementArray().size(), 0);
    EXPECT_EQ(t_board.At(1)->GetElementArray().size(), 1);
    EXPECT_EQ(t_board.At(1)->At(0)->GetData().title, "TestCard");
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

    // invalid card index
    EXPECT_THROW(
        t_board.MoveCard(
            {0, 0}, {1, 0});
            , std::out_of_range);
    
    // invalid list index
    t_board.At(0)->AddElement(Card( {"testcard"} ));

    EXPECT_THROW(
        t_board.MoveCard(
            {3, 0},
            {1, 0});
        , std::out_of_range);
}