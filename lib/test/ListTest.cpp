#include <gtest/gtest.h>
#include "List.hpp"

TEST(List, BaseConstructor) {
    List list("test");
   
    EXPECT_EQ(list.GetName(), "test");
    EXPECT_EQ(list.GetCards().size(), 0);
}

TEST(List, SetFunctions) {
    List list("test");

    list.SetName("changed");
    EXPECT_EQ(list.GetName(), "changed");
}

TEST(List, GetData) {
    List list("test");
    List::Data data = list.GetData();

    EXPECT_EQ(data.name, "test");
}

TEST(List, AddCard) {
    List List("test");

    List.AddCard(Card("testcard"));
    EXPECT_EQ(List.GetCards().size(), 1);

    List.AddCard(std::make_shared<Card>("testcard"));
    EXPECT_EQ(List.GetCards().size(), 2);
}

TEST(List, RemoveCard) {
    List list("test");
    list.AddCard(Card("testcard"));
    List::CardArray& lists = list.GetCardsRef();

    list.RemoveCard(lists.begin());
    EXPECT_EQ(lists.size(), 0);
}

TEST(List, Update) {
    List list("test");
    auto data = list.GetData();
    
    data.name = "changed";

    EXPECT_EQ(list.GetName(), "test");
    list.Update(data);
    EXPECT_EQ(list.GetName(), "changed");
}