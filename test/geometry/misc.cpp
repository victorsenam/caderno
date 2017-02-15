#include "gtest/gtest.h"
#include "../../code/geometry/misc.cpp"

TEST(misc, intersects) {
    pair<ll,ll> a(7,31);

    EXPECT_EQ(intersects(a, pair<ll,ll>(2,5)), -1);
    EXPECT_EQ(intersects(a, pair<ll,ll>(2,7)), 0);
    EXPECT_EQ(intersects(a, pair<ll,ll>(2,9)), 1);
    EXPECT_EQ(intersects(a, pair<ll,ll>(7,9)), 1);
    EXPECT_EQ(intersects(a, pair<ll,ll>(7,31)), 1);
    EXPECT_EQ(intersects(a, pair<ll,ll>(30,31)), 1);
    EXPECT_EQ(intersects(a, pair<ll,ll>(30,34)), 1);
    EXPECT_EQ(intersects(a, pair<ll,ll>(31,34)), 0);
    EXPECT_EQ(intersects(a, pair<ll,ll>(33,34)), -1);

    EXPECT_EQ(intersects(a, pair<ll,ll>(9,25)), 1);
    EXPECT_EQ(intersects(a, pair<ll,ll>(6,35)), 1);
}

TEST(misc, contains) {
    pair<ll,ll> a(7,31);
    
    EXPECT_EQ(contains(a, pair<ll,ll>(2,5)), -1);
    EXPECT_EQ(contains(a, pair<ll,ll>(2,7)), -1);
    EXPECT_EQ(contains(a, pair<ll,ll>(2,9)), -1);
    EXPECT_EQ(contains(a, pair<ll,ll>(7,9)), 0);
    EXPECT_EQ(contains(a, pair<ll,ll>(7,31)), 0);
    EXPECT_EQ(contains(a, pair<ll,ll>(30,31)), 0);
    EXPECT_EQ(contains(a, pair<ll,ll>(30,34)), -1);
    EXPECT_EQ(contains(a, pair<ll,ll>(31,34)), -1);
    EXPECT_EQ(contains(a, pair<ll,ll>(33,34)), -1);

    EXPECT_EQ(contains(a, pair<ll,ll>(9,25)), 1);
    EXPECT_EQ(contains(a, pair<ll,ll>(6,35)), -1);
}
