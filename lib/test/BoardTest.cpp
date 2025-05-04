#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "Board.hpp"

TEST(Board, BaseConstructor) {
    {
        Board board("test");
        const Board::ListArray& lists = board.GetLists();

        EXPECT_EQ(board.GetName(), "test");

        EXPECT_EQ(lists.size(), 3);
        for (const auto& list : lists)
            EXPECT_EQ(list->GetCards().size(), 0);
    }
    
    {
        Board::Data testData;
        testData.name = "test2";
        Board board2(testData);
        const Board::ListArray& lists2 = board2.GetLists();
        EXPECT_EQ(board2.GetName(), "test2");
        EXPECT_EQ(lists2.size(), 3);
        for (const auto& list : lists2)
            EXPECT_EQ(list->GetCards().size(), 0);
    }
}

TEST(Board, SetFunctions) {
    Board board("test");

    board.SetName("changed");
    EXPECT_EQ(board.GetName(), "changed");
}

TEST(Board, GetData) {
    Board board("test");
    auto data = board.GetData();
    EXPECT_EQ(board.GetName(), "test");
}

TEST(Board, Update) {
    Board board("test");
    auto data = board.GetData();

    data.name = "changed";

    EXPECT_EQ(board.GetName(), "test");
    board.Update(data);
    EXPECT_EQ(board.GetName(), "changed");
}

TEST(Board, AddList) {
    Board board("test");

    board.AddList(List("testlist"));
    EXPECT_EQ(board.GetLists().size(), 4);

    board.AddList(std::make_shared<List>("testlist"));
    EXPECT_EQ(board.GetLists().size(), 5);
}

TEST(Board, RemoveList) {
    Board board("test");
    Board::ListArray& lists = board.GetListsRef();

    board.RemoveList(lists.begin());
    EXPECT_EQ(lists.size(), 2);
}

TEST(Board, MoveCard) {
    Board board("test");
    Board::ListArray& lists = board.GetListsRef();
    board.RemoveList(lists.end() - 1);

    List::CardArray& cards1 = lists.at(0)->GetCardsRef();
    List::CardArray& cards2 = lists.at(1)->GetCardsRef();

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

TEST(Board, MoveCardErrors) {
    Board board("test");
    Board::ListArray& lists = board.GetListsRef();
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
    
    // source equal to destination
    EXPECT_THROW(
        board.MoveCard(
            lists.begin(), cardsBeginIt,
            lists.begin()); 
        ,
        std::out_of_range);
}