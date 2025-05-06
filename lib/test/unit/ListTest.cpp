#include <gtest/gtest.h>
#include "List.hpp"
#include "Card.hpp"

class ListTest : public testing::Test {
    protected:
    ListData t_data;
    List t_list;
    ListTest() 
        : t_list(t_data) { ; }
        
    void SetUp() override {
        t_data.name = "test";
        t_list = List(t_data);
    }
};

TEST_F(ListTest, BaseConstructor)
{
    {
        ListData data {"test2"};
        List list(data);
        EXPECT_EQ(list.GetDataRef().name, "test2");
        EXPECT_EQ(list.GetElementArray().size(), 0);
    }
}

TEST_F(ListTest, GetData)
{
    {
        auto data = t_list.GetData();
        EXPECT_EQ(data.name, "test");
    }
}

TEST_F(ListTest, AddCard)
{
    {
        t_list.AddElement(Card({ "testcard" }));
        EXPECT_EQ(t_list.GetElementArray().size(), 1);

        t_list.AddElement(std::make_shared<Card>(Card::Data{ "testcard" }));
        EXPECT_EQ(t_list.GetElementArray().size(), 2);
    }
}

TEST_F(ListTest, InsertCard)
{
    {
        // Insert at index = size()
        t_list.InsertElement(std::make_shared<Card>(Card::Data{"testcard"}), 0);
        EXPECT_EQ(t_list.GetElementArray().size(), 1);

        t_list.InsertElement(std::make_shared<Card>(Card::Data{"testcard2"}), 0);
        EXPECT_EQ(t_list.GetElementArray().size(), 2);

        t_list.InsertElement(std::make_shared<Card>(Card::Data{"testcard3"}), 1);
        EXPECT_EQ(t_list.GetElementArray().size(), 3);
        EXPECT_EQ(t_list.At(1)->GetDataRef().title, "testcard3");

        // Index out of range (-1), card expected to be added at the end
        t_list.InsertElement(std::make_shared<Card>(Card::Data{"testcard4"}), -1);
        EXPECT_EQ(t_list.GetElementArray().size(), 4);
        EXPECT_EQ(t_list.At(3)->GetDataRef().title, "testcard4");

        // Index in the middle
        t_list.InsertElement(std::make_shared<Card>(Card::Data{"testcard5"}), 2);
        EXPECT_EQ(t_list.GetElementArray().size(), 5);
        EXPECT_EQ(t_list.At(2)->GetDataRef().title, "testcard5");
    }
}

TEST_F(ListTest, RemoveCard)
{
    {
        t_list.AddElement(Card({ "testcard" }));

        t_list.RemoveElement(t_list.GetElementArray().begin());
        EXPECT_EQ(t_list.GetElementArray().size(), 0);
    }
}

TEST_F(ListTest, Update)
{
    {
        auto data = t_list.GetData();

        data.name = "changed";

        EXPECT_EQ(t_list.GetDataRef().name, "test");
        t_list.Update(data);
        EXPECT_EQ(t_list.GetDataRef().name, "changed");
    }
}