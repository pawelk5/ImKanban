#include <gtest/gtest.h>
#include "List.hpp"

TEST(List, BaseConstructor)
{
    {
        List list("test");

        EXPECT_EQ(list.GetName(), "test");
        EXPECT_EQ(list.GetCards().size(), 0);
    }

    {
        List::Data testData;
        testData.name = "test2";
        List list2(testData);
        EXPECT_EQ(list2.GetName(), "test2");
        EXPECT_EQ(list2.GetCards().size(), 0);
    }
}

TEST(List, SetFunctions)
{
    List list("test");

    list.SetName("changed");
    EXPECT_EQ(list.GetName(), "changed");
}

TEST(List, GetData)
{
    List list("test");
    List::Data data = list.GetData();

    EXPECT_EQ(data.name, "test");
}

TEST(List, AddCard)
{
    List List("test");

    List.AddCard(Card("testcard"));
    EXPECT_EQ(List.GetCards().size(), 1);

    List.AddCard(std::make_shared<Card>("testcard"));
    EXPECT_EQ(List.GetCards().size(), 2);
}

TEST(List, InsertCard)
{
    List List("test");

    List.AddCard(std::make_shared<Card>("testcard"));
    List.AddCard(std::make_shared<Card>("testcard2"));
    EXPECT_EQ(List.GetCards().size(), 2);

    List.InsertCard(std::make_shared<Card>("testcard3"), 1);
    EXPECT_EQ(List.GetCards().size(), 3);
    EXPECT_EQ(List.GetCards().at(1)->GetTitle(), "testcard3");

    // Index out of range (negative number), card expected to be added at the end
    List.InsertCard(std::make_shared<Card>("testcard4"), -1);
    EXPECT_EQ(List.GetCards().size(), 4);
    EXPECT_EQ(List.GetCards().at(3)->GetTitle(), "testcard4");

    // Index out of range (bigger than list length-1), card expected to be added at the end
    List.InsertCard(std::make_shared<Card>("testcard5"), 5);
    EXPECT_EQ(List.GetCards().size(), 5);
    EXPECT_EQ(List.GetCards().at(4)->GetTitle(), "testcard5");
}

TEST(List, RemoveCard)
{
    List list("test");
    list.AddCard(Card("testcard"));
    List::CardArray &lists = list.GetCardsRef();

    list.RemoveCard(lists.begin());
    EXPECT_EQ(lists.size(), 0);
}

TEST(List, Update)
{
    List list("test");
    auto data = list.GetData();

    data.name = "changed";

    EXPECT_EQ(list.GetName(), "test");
    list.Update(data);
    EXPECT_EQ(list.GetName(), "changed");
}