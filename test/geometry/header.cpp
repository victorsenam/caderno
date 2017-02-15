#include "gtest/gtest.h"
#include "../../code/geometry/header.cpp"

TEST(header, lt) {
    EXPECT_EQ(1, lt(-1, 1));
    EXPECT_EQ(0, lt(1, -1));


    EXPECT_EQ(0, lt(0));
    EXPECT_EQ(1, lt(-1));
    EXPECT_EQ(0, lt(1));
    EXPECT_EQ(0, lt(-1e-10));
    EXPECT_EQ(0, lt(1e-10));

    EXPECT_EQ(1, lte(0));
    EXPECT_EQ(1, lte(-1));
    EXPECT_EQ(0, lte(1));
    EXPECT_EQ(1, lte(-1e-10));
    EXPECT_EQ(1, lte(1e-10));

    EXPECT_EQ(1, lte(-1e-8));
}
