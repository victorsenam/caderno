#include "gtest/gtest.h"
#include "../../code/geometry/poly.cpp"

tmpl ::std::ostream& operator << (::std::ostream& os, const vec & a) {
    return os << "(" << a.x << "," << a.y << ")";
}

TEST(poly_resort, SortsPointsCounterClockwiseUsingLexicograficalMinimumAsAnchor) {
    vector<vect<ll> > v({
        vect<ll>(3,1), 
        vect<ll>(2,-1), 
        vect<ll>(1,2), 
        vect<ll>(-4,1)
    });
    poly<ll> pl(v);
    pl.resort();
    
    EXPECT_EQ(pl.v, vector<vect<ll> >({v[3], v[1], v[0], v[2]}));
}

TEST(poly_resort, WorksProperlyWithCollinearPoints) {
    vector<vect<ll> > v({
        vect<ll>(3,1), 
        vect<ll>(8,1),
        vect<ll>(5,3),
        vect<ll>(8,4),
        vect<ll>(8,6),
        vect<ll>(5,1),
        vect<ll>(4, 2), 
        vect<ll>(6,1)
    });
    poly<ll> pl(v);
    pl.resort();

    EXPECT_EQ(pl.v, vector<vect<ll> >({v[0], v[5], v[7], v[1], v[3], v[6], v[2], v[4]}));
}

vector<vect<ll> > base_point_set({
    vect<ll>(1,-2),
    vect<ll>(-2,-1),
    vect<ll>(0, 3),
    vect<ll>(4,0),
    vect<ll>(1,4),
    vect<ll>(3,-1),
    vect<ll>(2,4)
});

TEST(poly_graham, WorksProperlyWhenGivenSetIsConvex) {
    poly<ll> a(base_point_set), b(base_point_set);
    a.resort();
    b.graham();
    
    EXPECT_EQ(a.v,b.v);
}

TEST(poly_graham, WorksProperlyWhenGivenSetHasInnerPoints) {
    poly<ll> a(base_point_set), b(base_point_set);
    a.resort();

    b.v.insert(b.v.end(), {
        vect<ll>(0,0),
        vect<ll>(1,-1),
        vect<ll>(2,3),
        vect<ll>(0,3),
        vect<ll>(2,0)
    });
    b.graham();

    EXPECT_EQ(a.v,b.v);
}

TEST(poly_graham, WorksProperlyWhenGivenSetHasBorderPoints) {
    poly<ll> a(base_point_set), b(base_point_set);
    a.resort();

    b.v.insert(b.v.end(), {
        vect<ll>(-1, 1),
        vect<ll>(3, 2)
    });
    b.graham();

    EXPECT_EQ(a.v,b.v);
}

TEST(poly_graham, WorksProperlyWhenGivenSetHasBorderAndInnerPoints) {
    poly<ll> a(base_point_set), b(base_point_set);
    a.resort();

    b.v.insert(b.v.end(), {
        vect<ll>(0,0),
        vect<ll>(1,-1),
        vect<ll>(2,3),
        vect<ll>(0,3),
        vect<ll>(2,0),
        vect<ll>(-1,1),
        vect<ll>(3,2)
    });
    b.graham();

    EXPECT_EQ(a.v,b.v);
}

TEST(poly_graham, WorksProperlyWithManyPointsBetweenLastAndFirst) {
    poly<ll> a({
        vect<ll>(3,2),
        vect<ll>(3,10),
        vect<ll>(6,2),
    });
    poly<ll> b = a;

    b.v.insert(b.v.end(), {
        vect<ll>(3,6),
        vect<ll>(3,7),
        vect<ll>(3,4),
        vect<ll>(5,2),
        vect<ll>(4,2)
    });

    a.resort();
    b.graham();

    EXPECT_EQ(a.v,b.v);
}

TEST(poly_graham, WorksProperlyWhenAllPointsAreCollinear) {
    poly<ll> a({
        vect<ll>(1, 4),
        vect<ll>(2, 8),
        vect<ll>(4, 16),
        vect<ll>(-5, -20)
    });

    poly<ll> b = a;

    b.graham();

    EXPECT_EQ(b.v, vector<vect<ll> >({a.v[3], a.v[2]}));
} 
