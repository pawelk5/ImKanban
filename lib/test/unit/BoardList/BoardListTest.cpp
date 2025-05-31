#include <exception>
#include <gtest/gtest.h>
#include "BoardList.hpp"
#include "Board.hpp"

/// Test suite for Card class
class BoardListTest : public testing::Test
{
protected:
    BoardListData t_data;
    BoardList t_list;

    /// Constructor that initializes the boardlist with default data, doesnt load from file
    BoardListTest()
        : t_list(t_data, false) {}

    /// Setup function to initialize data before every test
    void SetUp() override
    {
        t_data.filepath = "";
        t_list = BoardList(t_data, false);
    }
};

/// Test for Card constructor
/// Verifies if constructor stores data properly
TEST_F(BoardListTest, SaveAndLoadFromFile)
{
    {
        t_list.Update(BoardListData{"test.json"});
        
        t_list.AddElement(BoardData{"TestName1", "filepath1.json"});
        t_list.AddElement(BoardData{"TestName2", "filepath2.json"});

        EXPECT_NO_THROW(t_list.SaveToFile());
        
        /// Remove all elements
        t_list.RemoveElement(0);
        t_list.RemoveElement(0);

        EXPECT_NO_THROW(t_list.LoadFromFile());

        EXPECT_EQ(t_list.GetElementArray().size(), 2);

        EXPECT_EQ(t_list.At(0)->name, "TestName1");
        EXPECT_EQ(t_list.At(1)->name, "TestName2");

        EXPECT_EQ(t_list.At(0)->filename, "filepath1.json");
        EXPECT_EQ(t_list.At(1)->filename, "filepath2.json");
    }
}

TEST_F(BoardListTest, LoadFromFileError)
{
    {
        t_list.Update(BoardListData{"empty.json"});

        EXPECT_THROW(t_list.LoadFromFile(), std::exception);

        EXPECT_EQ(t_list.GetElementArray().size(), 0);

        // set to empty filepath
        t_list.Update(BoardListData{""});
    }
}
