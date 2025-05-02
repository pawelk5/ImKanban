#include <gtest/gtest.h>
#include "List.hpp"

TEST(List, BaseConstructor) {
    List board("test");
   
    EXPECT_EQ(board.GetName(), "test");
    EXPECT_EQ(board.GetCards().size(), 0);
}