#include <gtest/gtest.h>
#include "List.hpp"


/// Test suite for List class
/// For now this is a placeholder, as there are no list-specific functions (all of them are derived from ContainerBase class)
class ListTest : public testing::Test {
    protected:
    ListData t_data;
    List t_list;

    /// Constructor that initializes the card with empty data
    ListTest() 
        : t_list(t_data) { ; }
    
    /// Setup function to initialize data before every test
    void SetUp() override {
        t_data.name = "test";
        t_list = List(t_data);
    }
};

TEST_F(ListTest, Placeholder)
{
    {
        SUCCEED();
    }
}