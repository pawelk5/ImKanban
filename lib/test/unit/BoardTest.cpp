#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "Board.hpp"
#include "List.hpp"


class BoardTest : public testing::Test {
protected:
    BoardData t_data;
    Board t_board;
    BoardTest() 
        : t_board(t_data) { ; }
    
    void SetUp() override {
        t_data.name = "test";
        t_board = Board(t_data);
    }
};

TEST_F(BoardTest, BaseConstructor)
{
    {
        BoardData data {"test2"};
        Board board(data);
        const auto &lists = board.GetElementArray();
        const auto &boardDataRef = board.GetDataRef();
        EXPECT_EQ(boardDataRef.name, "test2");

        EXPECT_EQ(lists.size(), 3);
        for (const auto &list : lists)
            EXPECT_EQ(list->GetElementArray().size(), 0);
    }
}

TEST_F(BoardTest, GetData)
{
    {
        auto data = t_board.GetData();
        EXPECT_EQ(data.name, "test");
    }
}

TEST_F(BoardTest, Update)
{
    {
        auto data = t_board.GetData();

        data.name = "changed";

        EXPECT_EQ(t_board.GetDataRef().name, "test");
        t_board.Update(data);
        EXPECT_EQ(t_board.GetDataRef().name, "changed");
    }
}

TEST_F(BoardTest, AddList)
{
    {
        t_board.AddElement(List({"testlist"}));
        EXPECT_EQ(t_board.GetElementArray().size(), 4);

        t_board.AddElement(std::make_shared<List>( ListData{ "testlist" } ));
        EXPECT_EQ(t_board.GetElementArray().size(), 5);
    }
}

TEST_F(BoardTest, RemoveList)
{
    {
        t_board.RemoveElement(0);
        EXPECT_EQ(t_board.GetElementArray().size(), 2);

        t_board.RemoveElement(t_board.GetElementArray().size() - 1);
        EXPECT_EQ(t_board.GetElementArray().size(), 1);

        t_board.RemoveElement(0);
        EXPECT_EQ(t_board.GetElementArray().size(), 0);
    }
}

TEST_F(BoardTest, RemoveListErrors)
{
    {
        EXPECT_THROW(t_board.RemoveElement(-1), std::out_of_range);
        EXPECT_THROW(t_board.RemoveElement(t_board.GetElementArray().size()), std::out_of_range);
        t_board.RemoveElement(0);
        t_board.RemoveElement(0);
        t_board.RemoveElement(0);
        EXPECT_THROW(t_board.RemoveElement(0), std::out_of_range);
    }
}

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

TEST_F(BoardTest, MoveCardErrors)
{
    auto &lists = t_board.GetElementArray();

    // invalid card iterator
    EXPECT_THROW(
        t_board.MoveCard(
            {0, 0}, {1, 0});
            , std::out_of_range);
    t_board.At(0)->AddElement(Card( {"testcard"} ));

    // invalid list iterator
    EXPECT_THROW(
        t_board.MoveCard(
            {3, 0},
            {1, 0});
        , std::out_of_range);
}