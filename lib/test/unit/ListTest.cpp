#include <gtest/gtest.h>
#include "List.hpp"
#include "Card.hpp"

List GetDefaultList() {
    ListData data;
    data.name = "test";
    List list(data);
    return list;
}

TEST(List, BaseConstructor)
{
    {
        auto list = GetDefaultList();
        EXPECT_EQ(list.GetDataRef().name, "test");
        EXPECT_EQ(list.GetElementArray().size(), 0);
    }
}

TEST(List, GetData)
{
    {
        auto list = GetDefaultList();
        EXPECT_EQ(list.GetData().name, "test");
    }
}

TEST(List, AddCard)
{
    {
        auto list = GetDefaultList();

        list.AddElement(Card({ "testcard" }));
        EXPECT_EQ(list.GetElementArray().size(), 1);

        list.AddElement(std::make_shared<Card>(Card::Data{ "testcard" }));
        EXPECT_EQ(list.GetElementArray().size(), 2);
    }
}

TEST(List, InsertCard)
{
    {
        auto list = GetDefaultList();

        // Insert at index = size()
        list.InsertElement(std::make_shared<Card>(Card::Data{"testcard"}), 0);
        EXPECT_EQ(list.GetElementArray().size(), 1);

        list.InsertElement(std::make_shared<Card>(Card::Data{"testcard2"}), 0);
        EXPECT_EQ(list.GetElementArray().size(), 2);

        list.InsertElement(std::make_shared<Card>(Card::Data{"testcard3"}), 1);
        EXPECT_EQ(list.GetElementArray().size(), 3);
        EXPECT_EQ(list.At(1)->GetDataRef().title, "testcard3");

        // Index out of range (-1), card expected to be added at the end
        list.InsertElement(std::make_shared<Card>(Card::Data{"testcard4"}), -1);
        EXPECT_EQ(list.GetElementArray().size(), 4);
        EXPECT_EQ(list.At(3)->GetDataRef().title, "testcard4");

        // Index in the middle
        list.InsertElement(std::make_shared<Card>(Card::Data{"testcard5"}), 2);
        EXPECT_EQ(list.GetElementArray().size(), 5);
        EXPECT_EQ(list.At(2)->GetDataRef().title, "testcard5");
    }
}

TEST(List, RemoveCard)
{
    {
        auto list = GetDefaultList();
        list.AddElement(Card({ "testcard" }));

        list.RemoveElement(list.GetElementArray().begin());
        EXPECT_EQ(list.GetElementArray().size(), 0);
    }
}

TEST(List, Update)
{
    {
        auto list = GetDefaultList();
        auto data = list.GetData();

        data.name = "changed";

        EXPECT_EQ(list.GetDataRef().name, "test");
        list.Update(data);
        EXPECT_EQ(list.GetDataRef().name, "changed");
    }
}