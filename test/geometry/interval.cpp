#include "gtest/gtest.h"
#include "../../code/geometry/interval.cpp"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

TEST(interval, contructor_one_argument) {
    interval<ll> in(-1);
    EXPECT_EQ(-1, in.a);
    EXPECT_EQ(-1, in.b);
}

TEST(interval, constructor_standart) {
    interval<ll> in(-1, 1);
    EXPECT_EQ(-1, in.a);
    EXPECT_EQ(1, in.b);
}

TEST(interval, constructor_swap) {
    interval<ll> in(42, -34);
    EXPECT_EQ(-34, in.a);
    EXPECT_EQ(42, in.b);
}

TEST(interval, contains_ll) {
    mt19937_64 gen(42);

    const ll ts[3][2] = {
        {3, 8},
        {0, 7000000000},
        {LLONG_MIN + 100, LLONG_MAX - 100}
    };

    for (int k = 0; k < 3; k++) {
        interval<ll> in(ts[k][0], ts[k][1]);
        
        EXPECT_EQ(1, in.contains(in.a));
        EXPECT_EQ(1, in.contains(in.b));
        EXPECT_EQ(1, in.contains(in));

        uniform_int_distribution<ll> mid(in.a+1, in.b-1);
        uniform_int_distribution<ll> gt(in.b+1, LLONG_MAX);
        uniform_int_distribution<ll> lt(LLONG_MIN, in.a-1);

        for (int i = 0; i < 5; i++) {
            EXPECT_EQ(1, in.contains(mid(gen)));

            interval<ll> ot(mid(gen), mid(gen));
            EXPECT_EQ(1, in.contains(ot));

            ot = interval<ll>(lt(gen), mid(gen));
            EXPECT_EQ(0, in.contains(ot));

            ot = interval<ll>(lt(gen), gt(gen));
            EXPECT_EQ(0, in.contains(ot));

            ot = interval<ll>(mid(gen), gt(gen));
            EXPECT_EQ(0, in.contains(ot));
        }
    }
}

TEST(interval, contains_double) {
    interval<double> in(-1e4, 1e4);

    EXPECT_EQ(1, in.contains(interval<double>(0), 1e-6));
    EXPECT_EQ(1, in.contains(interval<double>(1e4 - 1e-6), 1e-6));
    EXPECT_EQ(1, in.contains(interval<double>(1e4), 1e-6));
    EXPECT_EQ(0, in.contains(interval<double>(1e4 + 1e-6), 1e-6));
}
