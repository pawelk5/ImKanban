#include <gtest/gtest.h>
#include "Card.hpp"

class CardTest : public testing::Test {
protected:
    CardData t_data;
    Card t_card;
    CardTest() 
        : t_card(t_data) { ; }

    void SetUp() override {
        t_data.title = "test";
        t_card = Card(t_data);
    }
};


TEST_F(CardTest, BaseConstructor) {
    {
        CardData testData;
        testData.title = "test2";
        Card card2(testData);
        EXPECT_EQ(card2.GetDataRef().title, "test2");
    }
}

TEST_F(CardTest, GetData) {
    auto data = t_card.GetData();
    EXPECT_EQ(data.title, "test");
}

TEST_F(CardTest, Update) {
    auto data = t_card.GetData();

    data.title = "changed";

    EXPECT_EQ(t_card.GetDataRef().title, "test");
    t_card.Update(data);
    EXPECT_EQ(t_card.GetDataRef().title, "changed");
}