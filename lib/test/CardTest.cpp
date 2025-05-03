#include <gtest/gtest.h>
#include "Card.hpp"

TEST(Card, CardConstructor) {
    Card card("test");
    EXPECT_EQ(card.GetTitle(), "test");
}

TEST(Card, SetFunctions) {
    Card card("test");

    card.SetTitle("example");
    EXPECT_EQ(card.GetTitle(), "example");
}