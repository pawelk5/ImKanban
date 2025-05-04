#include <gtest/gtest.h>
#include "Card.hpp"

TEST(Card, CardConstructor) {
    Card card("test");
    EXPECT_EQ(card.GetTitle(), "test");
}

TEST(Card, GetData) {
    Card card("test");

    auto data = card.GetData();
    EXPECT_EQ(data.title, "test");
}

TEST(Card, SetFunctions) {
    Card card("test");

    card.SetTitle("example");
    EXPECT_EQ(card.GetTitle(), "example");
}

TEST(Card, Update) {
    Card card("test");
    auto data = card.GetData();

    data.title = "changed";

    EXPECT_EQ(card.GetTitle(), "test");
    card.Update(data);
    EXPECT_EQ(card.GetTitle(), "changed");
    
}