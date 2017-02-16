#include "gtest/gtest.h"
#include "../../code/geometry/vect.cpp"

TEST(vect_constructor, CreatesProperInstance) {
    vect<ll> in(-1, 1);
    EXPECT_EQ(-1, in.x);
    EXPECT_EQ(1, in.y);
}

TEST(vect_basic, BasicOperationsWorkProperly) {
    vect<ll> a(0,2), b(1,3);
    ll c = 2;
    vect<ll> d;

    d = a-b;
    EXPECT_EQ(-1, d.x);
    EXPECT_EQ(-1, d.y);

    d = a+b;
    EXPECT_EQ(1, d.x);
    EXPECT_EQ(5, d.y);

    d = b*c;
    EXPECT_EQ(2, d.x);
    EXPECT_EQ(6, d.y);

    d = b/c;
    EXPECT_EQ(0, d.x);
    EXPECT_EQ(1, d.y);
}

TEST(vect_rotate, RotatesCounterClockwise) {
    vect<ll> a(1, 2);
    EXPECT_DOUBLE_EQ(-1., a.rotate(pi).x);
    EXPECT_DOUBLE_EQ(-2., a.rotate(pi).y);

    EXPECT_DOUBLE_EQ(-2., a.rotate(.5*pi).x);
    EXPECT_DOUBLE_EQ(1., a.rotate(.5*pi).y);
}

TEST(vect_math, OperationsWorkProperly) {
    vect<ll> a(1,3), b(2,4), c(2,3);
    EXPECT_EQ(-2, a^b);
    EXPECT_EQ(14, a*b);
    EXPECT_EQ(2, a.sq(b));
    EXPECT_DOUBLE_EQ(sqrt(2.), a.nr(b));
}

TEST(vect_math, AreaIsCounterClockwiseOriented) {
    vect<ll> a(1,3), b(2,4), c(2,3);
    EXPECT_EQ(1, a.ar(c,b));
    EXPECT_EQ(-1, a.ar(b,c));
}

TEST(vect_lexcompare, ReturnsFalseIfaIsLessThanb) {
    vect<ll> a(1,4), b(3,2), c(4,3), d(4,-34);

    EXPECT_FALSE(b < a);
    EXPECT_FALSE(a < a);
    EXPECT_FALSE(c < d);
}

TEST(vect_lexcompare, ReturnsTrueIfbIsLessThana) {
    vect<ll> a(1,4), b(3,2), c(5,6), d(1, 0);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b < c);
    EXPECT_TRUE(d < a);
}

TEST(vect_left, ReturnsLessThan0IfcIsToTheLeftOfab) {
    vect<ll> a(1,4), b(3,2), c(5,6);
    EXPECT_LT(a.left(b,c), 0);
}

TEST(vect_left, ReturnsGreaterThan0IfcIsToTheRightOfab) {
    vect<ll> a(1,4), b(3,2), c(5,6);
    EXPECT_GT(b.left(a,c), 0);
}

TEST(vect_left, ReturnsEqualTo0IfcIsCollinearWithab) {
    vect<ll> b(3,2), c(5,6), d(12, 8), e(-12, -8);
    EXPECT_EQ(b.left(d,e), 0);
    EXPECT_EQ(d.left(b,e), 0);
    EXPECT_EQ(e.left(b,d), 0);
}

TEST(vect_halfplane, ReturnsFalseIfaIsLessThan180degFromAnchor) {
    vect<ll> a(1,4), b(3,2), c(5,6), d(12, 8), e(-12, -8), f(-1, 0), g(1, 0);
    EXPECT_EQ(a.halfplane(), 0);
    EXPECT_EQ(g.halfplane(), 0);
    EXPECT_EQ(c.halfplane(c), 0);
    EXPECT_EQ(e.halfplane(vect<ll>(0,1)), 0);
}

TEST(vect_halfplane, ReturnsFalseIfAtLeast180degFromAnchor) {
    vect<ll> a(1,4), b(3,2), c(5,6), d(12, 8), e(-12, -8), f(-1, 0), g(1, 0);
    EXPECT_EQ(e.halfplane(), 1);
    EXPECT_EQ(f.halfplane(), 1);
    EXPECT_EQ(b.halfplane(c), 1);
    EXPECT_EQ(d.halfplane(vect<ll>(0,1)), 1);
}

TEST(vect_compare, ReturnsTrueIfaComesBeforebFromAnchorInCounterClockwise) {
    vect<ll> a(1,4), b(3,2), c(5,6), d(12, 8), e(-12, -8), f(-1, 0), g(1, 0);
    EXPECT_TRUE(a.compare(e));
    EXPECT_TRUE(b.compare(d));
}

TEST(vect_compare, ReturnsFalseIfaComesAfterbFromAnchorInCounterClockwise) {
    vect<ll> a(1,4), b(3,2), c(5,6), d(12, 8), e(-12, -8), f(-1, 0), g(1, 0);
    EXPECT_FALSE(d.compare(b));
}
