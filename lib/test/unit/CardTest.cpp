#include <gtest/gtest.h>
#include "Card.hpp"

Card GetDefaultCard() {
    Card::Data data;
    data.title = "test";
    Card card(data);
    return card;
}

TEST(Card, BaseConstructor) {
    {
        Card::Data testData;
        testData.title = "test2";
        Card card2(testData);
        EXPECT_EQ(card2.GetTitle(), "test2");
    }
}

TEST(Card, GetData) {
    auto card = GetDefaultCard();

    auto data = card.GetData();
    EXPECT_EQ(data.title, "test");
}

TEST(Card, SetFunctions) {
    auto card = GetDefaultCard();

    card.SetTitle("example");
    EXPECT_EQ(card.GetTitle(), "example");
}

TEST(Card, Update) {
    auto card = GetDefaultCard();
    auto data = card.GetData();

    data.title = "changed";

    EXPECT_EQ(card.GetTitle(), "test");
    card.Update(data);
    EXPECT_EQ(card.GetTitle(), "changed");
}