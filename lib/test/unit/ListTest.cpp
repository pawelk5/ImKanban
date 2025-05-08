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

TEST_F(ListTest, Placeholder)
{
    {
        EXPECT_TRUE(true);
    }
}