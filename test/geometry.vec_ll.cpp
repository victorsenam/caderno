typedef long long cood;
const cood eps = 0;

#include "gtest/gtest.h"
#include "../code/geometry.cpp"

bool operator== (vec a, vec b)
{ return a.x == b.x && a.y == b.y; }

TEST(geometry_vec_ll, BasicOperations) {
    vec a(45,16), b(50,13);
    ll c = 10;

    EXPECT_EQ(a.x, 45);
    EXPECT_EQ(a.y, 16);

    EXPECT_EQ(a-b, vec(-5, 3));
    EXPECT_EQ(a+b, vec(95, 29));
    EXPECT_EQ(a*c, vec(450, 160));
    EXPECT_EQ(a/c, vec(4, 1));

    EXPECT_EQ(a^b, -215);
    EXPECT_EQ(a*b, 2458);

    EXPECT_EQ(a.sq(), 2281);
    EXPECT_DOUBLE_EQ(a.nr(), sqrt(a.sq()));
}

TEST(geometry_vec_ll, OrientedArea) {
    EXPECT_EQ(vec(0,2).sd(vec(1,0),vec(3,2)), -1) << "should return -1 when left";  // left
    EXPECT_EQ(vec(2,0).sd(vec(1,0),vec(3,2)), 1); // right
    EXPECT_EQ(vec(2,1).sd(vec(1,0),vec(3,2)), 0); // colin
    EXPECT_EQ(vec(2,1).sd(vec(3,2),vec(1,0)), 0); // colin
    EXPECT_EQ(vec(1,0).sd(vec(2,1),vec(3,2)), 0); // before line
    EXPECT_EQ(vec(1,0).sd(vec(3,2),vec(2,1)), 0); // after line
    EXPECT_EQ(vec(-50,-48).sd(vec(-49,-50),vec(-47,-48)), -1); // all neg
    EXPECT_EQ(vec(-3, 1).sd(vec(1,-5),vec(-4,10)), -1); // mixed

    EXPECT_EQ(vec(11,-11).sd(vec(0,0),vec(-1,0)), -1); // extra test

    EXPECT_EQ(vec(99,101).ar(vec(100,100),vec(101,101)), 2);
    EXPECT_EQ(vec(10,13).ar(vec(80,83),vec(-20,-17)), 0);
}

TEST(geometry_vec_ll, HalfPlane) {
    EXPECT_TRUE(vec(-1,0).halfplane());
    EXPECT_FALSE(vec(0,0).halfplane());
    EXPECT_FALSE(vec(1,0).halfplane());
    EXPECT_TRUE(vec(-7274,0).halfplane());
    EXPECT_TRUE(vec(32,-42).halfplane());
    EXPECT_TRUE(vec(-41, -231).halfplane());
    EXPECT_FALSE(vec(-232, 182).halfplane());
    EXPECT_FALSE(vec(415, 3214).halfplane());
    EXPECT_TRUE(vec(11,-11).halfplane());

    EXPECT_FALSE(vec(50, 50).halfplane(vec(100,100)));
    EXPECT_TRUE(vec(-50, -50).halfplane(vec(100,100)));
    EXPECT_FALSE(vec().halfplane(vec(100,100)));
    EXPECT_TRUE(vec(10,0).halfplane(vec(100,100)));
}

TEST(geometry_vec_ll, Compare) {
    EXPECT_TRUE(vec(1,0).compare(vec(0,1)));
    EXPECT_TRUE(vec(1,0).compare(vec(2,0)));
    EXPECT_FALSE(vec(-1,0).compare(vec(1,0)));
    EXPECT_FALSE(vec(11,-11).compare(vec(-1,0)));

    vector<vec> ans({
        vec(3,0), vec(10,0),
        vec(3,1),
        vec(4,4), vec(748, 748),
        vec(0,5),
        vec(-1,0), vec(-2,0),
        vec(-1,-4),
        vec(401, -4)
    });

    vector<vec> res = ans;
    srand(42); rand(); rand();
    random_shuffle(res.begin(), res.end());
    sort(res.begin(), res.end(), [] (vec a, vec b) { return a.compare(b); });
    
    EXPECT_EQ(res, ans);
}

