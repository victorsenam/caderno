#include "gtest/gtest.h"
#include "../../code/geometry/vect.cpp"

TEST(vect, contructor) {
    vect<ll> in(-1, 1);
    EXPECT_EQ(-1, in.x);
    EXPECT_EQ(1, in.y);
}

TEST(vect, basic_transforming) {
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

TEST(vect, rotate) {
    vect<ll> a(1, 2);
    EXPECT_DOUBLE_EQ(-1., a.rotate(pi).x);
    EXPECT_DOUBLE_EQ(-2., a.rotate(pi).y);

    EXPECT_DOUBLE_EQ(-2., a.rotate(.5*pi).x);
    EXPECT_DOUBLE_EQ(1., a.rotate(.5*pi).y);
}

TEST(vect, math) {
    vect<ll> a(1,3), b(2,4), c(2,3);
    EXPECT_EQ(-2, a^b);
    EXPECT_EQ(14, a*b);
    EXPECT_EQ(2, a.sq(b));
    EXPECT_DOUBLE_EQ(sqrt(2.), a.nr(b));
    EXPECT_EQ(1, a.ar(c,b));
    EXPECT_EQ(-1, a.ar(b,c));
}

TEST(vect, ordering) {
    vect<ll> a(1,4), b(3,2), c(5,6), d(12, 8), e(-12, -8), f(-1, 0), g(1, 0);

    EXPECT_EQ(1, a < b);
    EXPECT_EQ(0, b < a);
    EXPECT_EQ(1, b < c);
    EXPECT_EQ(0, a < a);
    EXPECT_EQ(1, g < a);
    EXPECT_EQ(0, vect<ll>(4,3) < vect<ll>(4, -34));

    EXPECT_EQ(-1, a.left(b,c));
    EXPECT_EQ(1, b.left(a,c));
    EXPECT_EQ(0, b.left(d,e));
    EXPECT_EQ(0, d.left(b,e));
    EXPECT_EQ(0, e.left(b,d));

    EXPECT_EQ(0, a.halfplane());
    EXPECT_EQ(1, e.halfplane());
    EXPECT_EQ(1, f.halfplane());
    EXPECT_EQ(0, g.halfplane());
    
    EXPECT_EQ(0, c.halfplane(c));
    EXPECT_EQ(1, b.halfplane(c));

    EXPECT_EQ(1, d.halfplane(vect<ll>(0,1)));
    EXPECT_EQ(0, e.halfplane(vect<ll>(0,1)));

    EXPECT_EQ(1, a.compare(e));
    EXPECT_EQ(1, b.compare(d));
    EXPECT_EQ(0, d.compare(b));
}
