#include "gtest/gtest.h"
#include "../../code/math/fft.cpp"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<double> cpx;

TEST(fft, simple_real) {
    vector<cpx> a({5,3,2,7});
    vector<cpx> b({3,5,1,6});
    vector<cpx> c({15,34,26,64,55,19,42,0});
    vector<cpx> d = product(a,b);
    
    ASSERT_EQ(c.size(), d.size());

    for (unsigned int i = 0; i < c.size(); i++)
        EXPECT_DOUBLE_EQ(c[i].real(), d[i].real());
}

vector<cpx> naive (const vector<cpx> & a, const vector<cpx> & b) {
    vector<cpx> c(a.size() + b.size() - 1, 0);

    for (unsigned int i = 0; i < a.size(); i++)
        for (unsigned int j = 0; j < b.size(); j++)
            c[i+j] += a[i] * b[j];
    return c;
}

TEST(fft, STRESS_complex) {
    mt19937_64 gen(42);
    uniform_int_distribution<int> rnd_size(3, 1000);
    uniform_real_distribution<double> rnd_value(-10, 10);

    int tc = 50;
    while (tc--) {
        vector<cpx> a(rnd_size(gen)), b(rnd_size(gen));

        for (unsigned int i = 0; i < a.size(); i++)
            a[i] = cpx(rnd_value(gen), rnd_value(gen));
        for (unsigned int i = 0; i < b.size(); i++)
            b[i] = cpx(rnd_value(gen), rnd_value(gen));

        vector<cpx> c = naive(a,b);
        vector<cpx> d = product(a,b);

        ASSERT_GE(d.size(), c.size());
        c.resize(d.size(), 0);
        for (unsigned int i = 0; i < c.size(); i++) {
            EXPECT_NEAR(c[i].real(), d[i].real(), 1e-9);
            EXPECT_NEAR(c[i].imag(), d[i].imag(), 1e-9);
        }
    }
}
