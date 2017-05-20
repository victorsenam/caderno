#define COOD_TYPE ll

#include "gtest/gtest.h"
#include "../code/geometry.cpp"

TEST(geometry_vec_ll, BasicOperations) {
    vec a(45,16), b(50,13);
    ll c = 10;

    EXPECT_EQ(a.x, 45);
    EXPECT_EQ(a.y, 16);

    EXPECT_EQ(a-b, vec(-5, 3));
    EXPECT_EQ(a+b, vec(95, 29));
    EXPECT_EQ(a*c, vec(450, 160));
    EXPECT_EQ(a/c, vec(4, 1));

    EXPECT_EQ(a^b, -285);
    EXPECT_EQ(a*b, 1108);

    EXPECT_EQ(a.sq(), 2281);
    EXPECT_DOUBLE_EQ(a.nr(), sqrt(a.sq()));
}

TEST(geometry_vec_ll, OrientedArea) {
    EXPECT_TRUE(vec(0,2).lf(vec(1,0),vec(3,2)));  // left
    EXPECT_FALSE(vec(2,0).lf(vec(1,0),vec(3,2))); // right
    EXPECT_FALSE(vec(2,1).lf(vec(1,0),vec(3,2))); // colin

    // left tests with neg numbers
    // correct value area tests
}
