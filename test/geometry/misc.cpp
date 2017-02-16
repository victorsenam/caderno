#include "gtest/gtest.h"
#include "../../code/geometry/misc.cpp"

TEST(misc_intersects, ReturnsLessThan0ForNonIntersecting) {
    pair<ll,ll> a(7,31);
    
    EXPECT_LT(intersects(a, pair<ll,ll>(2,5)), 0);
    EXPECT_LT(intersects(a, pair<ll,ll>(33,34)), 0);
}

TEST(misc_intersects, Returns0ForBorderOnlyIntersection) {
    pair<ll,ll> a(7,31);

    EXPECT_EQ(intersects(a, pair<ll,ll>(2,7)), 0);
    EXPECT_EQ(intersects(a, pair<ll,ll>(31,34)), 0);
}

TEST(misc_intersects, ReturnsGreaterThan0ForProperIntersection) {
    pair<ll,ll> a(7,31);

    EXPECT_GT(intersects(a, pair<ll,ll>(2,9)), 0);
    EXPECT_GT(intersects(a, pair<ll,ll>(7,9)), 0);
    EXPECT_GT(intersects(a, pair<ll,ll>(7,31)), 0);
    EXPECT_GT(intersects(a, pair<ll,ll>(30,31)), 0);
    EXPECT_GT(intersects(a, pair<ll,ll>(30,34)), 0);

    EXPECT_GT(intersects(a, pair<ll,ll>(9,25)), 0);
    EXPECT_GT(intersects(a, pair<ll,ll>(6,35)), 0);
}

TEST(misc_contains, ReturnsLessThan0ForNonContained) {
    pair<ll,ll> a(7,31);
    
    EXPECT_EQ(contains(a, pair<ll,ll>(2,5)), -1);
    EXPECT_EQ(contains(a, pair<ll,ll>(2,7)), -1);
    EXPECT_EQ(contains(a, pair<ll,ll>(2,9)), -1);

    EXPECT_EQ(contains(a, pair<ll,ll>(30,34)), -1);
    EXPECT_EQ(contains(a, pair<ll,ll>(31,34)), -1);
    EXPECT_EQ(contains(a, pair<ll,ll>(33,34)), -1);

    EXPECT_EQ(contains(a, pair<ll,ll>(6,35)), -1);
}

TEST(misc_contains, ReturnsEqualTo0ForBorderTouchingContained) {
    pair<ll,ll> a(7,31);

    EXPECT_EQ(contains(a, pair<ll,ll>(7,9)), 0);
    EXPECT_EQ(contains(a, pair<ll,ll>(7,31)), 0);
    EXPECT_EQ(contains(a, pair<ll,ll>(30,31)), 0);
}

TEST(misc_contains, ReturnsGreaterThan0ForStrictlyConatined) {
    pair<ll,ll> a(7,31);

    EXPECT_GT(contains(a, pair<ll,ll>(9,25)), 0);
}
