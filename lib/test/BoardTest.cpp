#include <gtest/gtest.h>
#include "Board.hpp"

TEST(Board, BaseConstructor) {
    Board board("test");
    const Board::ListArray& lists = board.GetLists();

    EXPECT_EQ(board.GetName(), "test");

    EXPECT_EQ(lists.size(), 3);
    for (const auto& list : lists)
        EXPECT_EQ(list->GetCards().size(), 0);
}

TEST(Board, SetFunctions) {
    Board board("test");
    EXPECT_EQ(board.GetName(), "test");

    board.SetName("changed");
    EXPECT_EQ(board.GetName(), "changed");
}