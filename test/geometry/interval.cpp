#include "gtest/gtest.h"
#include "../../code/geometry/interval.cpp"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

TEST(interval, contructors) {
    mt19937_64 gen(42);

    const int tss = 4;
    ll ts_arg[tss][2] = {
        {0, 1000000},
        {0, LLONG_MAX},
        {LLONG_MIN, LLONG_MAX},
        {10, 10}
    };
    const int ts_qt[tss] = {10, 10, 30};

    for (int ts = 0; ts < tss; ts++) {
        for (int tc = 0; tc < ts_qt[ts]; tc++) {
            assert(ts_arg[ts][0] <= ts_arg[ts][1]);
            uniform_int_distribution<ll> down(ts_arg[ts][0], ts_arg[ts][1]);
            ll lo = down(gen);

            // does it duplicate if it should?
            interval<ll> t1(lo);
            ASSERT_EQ(t1.a, lo);
            ASSERT_EQ(t1.b, lo);

            uniform_int_distribution<ll> up(lo, ts_arg[ts][1]);
            ll hi = up(gen);

            assert(lo <= hi);

            // do they keep order if they should?
            interval<ll> t2(lo, hi);
            ASSERT_EQ(t2.a, lo);
            ASSERT_EQ(t2.b, hi);

            // do they swap if necessary?
            interval<ll> t3(hi, lo);
            ASSERT_EQ(t3.a, lo);
            ASSERT_EQ(t3.b, hi);

        }
    }
}

/*
TEST(interval_ll_contains, True) {
    linear_congruential_engine generator;

    EXPECT_EQ(1, interval<ll>(-1, 1).contains(0));
    EXPECT_EQ(1, interval<ll>(-1, 1).contains(-1));

    interval_ll_contains(1, INT_MAX, generator, 10);
    interval_ll_contains(INT_MIN, INT_MAX, generator, 30);   
}

TEST(interval_ll_contains, False) {
}
*/
