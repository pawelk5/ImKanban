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

// TODO: Move MoveCard test to integration tests
/* 
TEST(Board, MoveCard)
{
    Board board("test");
    Board::ListArray &lists = board.GetListsRef();
    board.RemoveList(lists.end() - 1);

    List::CardArray &cards1 = lists.at(0)->GetCardsRef();
    List::CardArray &cards2 = lists.at(1)->GetCardsRef();

    lists.at(0)->AddCard(Card{"TestCard"});
    EXPECT_EQ(cards1.size(), 1);
    EXPECT_EQ(cards2.size(), 0);

    board.MoveCard(
        lists.begin(), cards1.begin(),
        lists.begin() + 1);

    EXPECT_EQ(cards1.size(), 0);
    EXPECT_EQ(cards2.size(), 1);

    board.MoveCard(
        lists.begin() + 1, cards2.begin(),
        lists.begin());

    EXPECT_EQ(cards1.size(), 1);
    EXPECT_EQ(cards2.size(), 0);
}

TEST(Board, MoveCardErrors)
{
    Board board("test");
    Board::ListArray &lists = board.GetListsRef();
    auto cardsBeginIt = (*lists.begin())->GetCardsRef().begin();

    // invalid card iterator
    EXPECT_THROW(
        board.MoveCard(
            lists.begin(), cardsBeginIt,
            lists.begin() + 1);
        ,
        std::out_of_range);
    (*lists.begin())->AddCard(Card{"testcard"});

    // invalid list iterator
    EXPECT_THROW(
        board.MoveCard(
            lists.end(), cardsBeginIt,
            lists.begin());
        ,
        std::out_of_range);
}
*/