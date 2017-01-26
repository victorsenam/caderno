#include "gtest/gtest.h"
#include "../../code/geometry/inte.cpp"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

TEST(inte, contructor_one_argument) {
    inte<ll> in(-1);
    EXPECT_EQ(-1, in.a);
    EXPECT_EQ(-1, in.b);
}

TEST(inte, constructor_standart) {
    inte<ll> in(-1, 1);
    EXPECT_EQ(-1, in.a);
    EXPECT_EQ(1, in.b);
}

TEST(inte, constructor_swap) {
    inte<ll> in(42, -34);
    EXPECT_EQ(-34, in.a);
    EXPECT_EQ(42, in.b);
}

TEST(inte, contains_ll) {
    mt19937_64 gen(42);

    const ll ts[3][2] = {
        {3, 8},
        {0, 7000000000},
        {LLONG_MIN + 100, LLONG_MAX - 100}
    };

    for (int k = 0; k < 3; k++) {
        inte<ll> in(ts[k][0], ts[k][1]);
        
        EXPECT_EQ(1, in.contains(inte<ll>(in.a)));
        EXPECT_EQ(1, in.contains(inte<ll>(in.b)));
        EXPECT_EQ(1, in.contains(in));

        uniform_int_distribution<ll> mid(in.a+1, in.b-1);
        uniform_int_distribution<ll> gt(in.b+1, LLONG_MAX);
        uniform_int_distribution<ll> lt(LLONG_MIN, in.a-1);

        for (int i = 0; i < 5; i++) {
            EXPECT_EQ(1, in.contains(inte<ll>(mid(gen))));

            inte<ll> ot(mid(gen), mid(gen));
            EXPECT_EQ(1, in.contains(ot));

            ot = inte<ll>(lt(gen), mid(gen));
            EXPECT_EQ(0, in.contains(ot));

            ot = inte<ll>(lt(gen), gt(gen));
            EXPECT_EQ(0, in.contains(ot));

            ot = inte<ll>(mid(gen), gt(gen));
            EXPECT_EQ(0, in.contains(ot));
        }
    }
}

TEST(inte, contains_double) {
    inte<double> in(-1e4, 1e4);

    EXPECT_EQ(1, in.contains(inte<double>(0), 1e-6));
    EXPECT_EQ(1, in.contains(inte<double>(1e4 - 1e-6), 1e-6));
    EXPECT_EQ(1, in.contains(inte<double>(1e4), 1e-6));
    EXPECT_EQ(0, in.contains(inte<double>(1e4 + 1e-6), 1e-6));
}

TEST(inte, intersects) {
    inte<ll> in(-3, 3);
    
    EXPECT_EQ(1, in.intersects(inte<ll>(-4, 0)));
    EXPECT_EQ(1, in.intersects(inte<ll>(0, 4)));
    EXPECT_EQ(1, in.intersects(inte<ll>(-2, 2)));
    EXPECT_EQ(1, in.intersects(inte<ll>(-4, 4)));

    EXPECT_EQ(0, in.intersects(inte<ll>(-10, -4)));
    EXPECT_EQ(0, in.intersects(inte<ll>(4, 10)));
}
