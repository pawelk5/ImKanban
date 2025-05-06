#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "Board.hpp"
#include "List.hpp"

Board GetDefaultBoard() {
    BoardData data;
    data.name = "test";
    Board board(data);
    return board;
}

TEST(Board, BaseConstructor)
{
    {
        auto board = GetDefaultBoard();
        const auto &lists = board.GetElementArray();
        const auto & boardDataRef = board.GetDataRef();
        EXPECT_EQ(boardDataRef.name, "test");

        EXPECT_EQ(lists.size(), 3);
        for (const auto &list : lists)
            EXPECT_EQ(list->GetElementArray().size(), 0);
    }
}

TEST(Board, GetData)
{
    {
        auto board = GetDefaultBoard();
        auto data = board.GetData();
        EXPECT_EQ(data.name, "test");
    }
}

TEST(Board, Update)
{
    {
        auto board = GetDefaultBoard();
        auto data = board.GetData();

        data.name = "changed";

        EXPECT_EQ(board.GetDataRef().name, "test");
        board.Update(data);
        EXPECT_EQ(board.GetDataRef().name, "changed");
    }
}

TEST(Board, AddList)
{
    {
        auto board = GetDefaultBoard();

        board.AddElement(List({"testlist"}));
        EXPECT_EQ(board.GetElementArray().size(), 4);

        board.AddElement(std::make_shared<List>( ListData{ "testlist" } ));
        EXPECT_EQ(board.GetElementArray().size(), 5);
    }
}

TEST(Board, RemoveList)
{
    {
        auto board = GetDefaultBoard();

        board.RemoveElement(0);
        EXPECT_EQ(board.GetElementArray().size(), 2);

        board.RemoveElement(board.GetElementArray().size() - 1);
        EXPECT_EQ(board.GetElementArray().size(), 1);

        board.RemoveElement(0);
        EXPECT_EQ(board.GetElementArray().size(), 0);
    }
}

TEST(Board, RemoveListErrors)
{
    {
        auto board = GetDefaultBoard();

        EXPECT_THROW(board.RemoveElement(-1), std::out_of_range);
        EXPECT_THROW(board.RemoveElement(board.GetElementArray().size()), std::out_of_range);
        board.RemoveElement(0);
        board.RemoveElement(0);
        board.RemoveElement(0);
        EXPECT_THROW(board.RemoveElement(0), std::out_of_range);
    }
}

TEST(Board, MoveCard)
{
    auto board = GetDefaultBoard();
    const auto &lists = board.GetElementArray();
    board.RemoveElement(lists.end() - 1);


    board.At(0)->AddElement(Card({"TestCard"}));
    EXPECT_EQ(board.At(0)->GetElementArray().size(), 1);
    EXPECT_EQ(board.At(1)->GetElementArray().size(), 0);

    board.MoveCard(
        {0, 0}, {1, 0});

    EXPECT_EQ(board.At(0)->GetElementArray().size(), 0);
    EXPECT_EQ(board.At(1)->GetElementArray().size(), 1);
    EXPECT_EQ(board.At(1)->At(0)->GetData().title, "TestCard");
    board.MoveCard(
        {1, 0},
        {0, 0});

        EXPECT_EQ(board.At(0)->GetElementArray().size(), 1);
        EXPECT_EQ(board.At(1)->GetElementArray().size(), 0);
        EXPECT_EQ(board.At(0)->At(0)->GetData().title, "TestCard");
}

TEST(Board, MoveCardErrors)
{
    auto board = GetDefaultBoard();
    auto &lists = board.GetElementArray();

    // invalid card iterator
    EXPECT_THROW(
        board.MoveCard(
            {0, 0}, {1, 0});
        , std::out_of_range);
    board.At(0)->AddElement(Card( {"testcard"} ));

    // invalid list iterator
    EXPECT_THROW(
        board.MoveCard(
            {3, 0},
            {1, 0});
        , std::out_of_range);
}