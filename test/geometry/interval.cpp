#include "gtest/gtest.h"
#include "../../code/geometry/interval.cpp"

TEST(interval_ll_contains, True) {
    EXPECT_EQ(1, interval<ll>(-1, 1).contains(0));
    EXPECT_EQ(1, interval<ll>(-1, 1).contains(-1));
}
