#include "gtest/gtest.h"
#include "../code/sample.cpp"

TEST(test_id, Thudo) {
    EXPECT_EQ(1, test_id(1));
    EXPECT_EQ(7, test_id(7));
}
