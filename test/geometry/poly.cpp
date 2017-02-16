#include "gtest/gtest.h"
#include "../../code/geometry/poly.cpp"

tmpl ::testing::AssertionResult AssertVectEqual(const char * a_expr, const char * b_expr, vect<cood> a, vect<cood> b) {
    if (lt(a.x,b.x) || lt(b.x,a.x))
        return ::testing::AssertionFailure()
            << a_expr << " (" << a.x << "," << a.y << ") and " << b_expr << " (" << b.x << "," << b.y << ") differ on x";
    if (lt(a.y,b.y) || lt(b.y,a.y))
        return ::testing::AssertionFailure()
            << a_expr << " (" << a.x << "," << a.y << ") and " << b_expr << " (" << b.x << "," << b.y << ") differ on y";

    return ::testing::AssertionSuccess();

}

TEST(poly, resort) {
    vector<vect<ll> > v({vect<ll>(3,1), vect<ll>(2,-1), vect<ll>(1,2), vect<ll>(-4,1)});
    poly<ll> pl(v);
    
    pl.resort();
    
    EXPECT_PRED_FORMAT2(AssertVectEqual, pl.v[0], v[3]);
    EXPECT_PRED_FORMAT2(AssertVectEqual, pl.v[1], v[1]);
    EXPECT_PRED_FORMAT2(AssertVectEqual, pl.v[2], v[0]);
    EXPECT_PRED_FORMAT2(AssertVectEqual, pl.v[3], v[2]);
}
