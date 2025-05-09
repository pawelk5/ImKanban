#include <gtest/gtest.h>
#include "Card.hpp"

/// Test suite for Card class
class CardTest : public testing::Test {
protected:
    CardData t_data;
    Card t_card;

    /// Constructor that initializes the card with empty data
    CardTest() 
        : t_card(t_data) { ; }

    /// Setup function to initialize data before every test
    void SetUp() override {
        t_data.title = "test";
        t_card = Card(t_data);
    }
};

/// Test for Card constructor
/// Verifies if constructor stores data properly
TEST_F(CardTest, BaseConstructor) {
    {
        CardData testData;
        testData.title = "test2";
        Card card2(testData);
        EXPECT_EQ(card2.GetDataRef().title, "test2");
    }
}

/// Test for GetData function
/// Verifies that GetData returns a copy of stored data
TEST_F(CardTest, GetData) {
    auto data = t_card.GetData();
    EXPECT_EQ(data.title, "test");

    data.title = "changed";
    EXPECT_EQ(t_card.GetData().title, "test");
}

/// Test for Update function
/// Verifies that Update changes stored data
TEST_F(CardTest, Update) {
    auto data = t_card.GetData();

    data.title = "changed";
    t_card.Update(data);
    EXPECT_EQ(t_card.GetDataRef().title, "changed");
}