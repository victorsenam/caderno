#include "gtest/gtest.h"
#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 112345;

#include "../../code/math/fft.cpp"

cpx a[112345], b[112345], c[112345];
int p[N];

TEST(FFT, Simple0) {
	a[0] = 666;
	b[0] = 999;
	FFT(a, c, 1, 1, p);
	EXPECT_EQ(c[0].real(), 666);
	FFT(b, a, 1, 1, p);
	EXPECT_EQ(a[0].real(), 999);
	a[0] *= c[0];
	FFT(a, b, 1, -1, p);
	EXPECT_EQ(b[0].real(), 666 * 999);
}

TEST(FFT, Simple1) {
	int i;
	for(i = 0; i < 8; i++) a[i] = b[i] = c[i] = 0;
	for(i = 8; i < 100; i++) a[i] = rand(), b[i] = rand(), c[i] = rand();
	i = 0;
	for(int x : {5, 3, 2, 7}) a[i++] = x;
	i = 0;
	for(int x : {3, 5, 1, 6}) b[i++] = x;

	FFT(a, c, 8, 1, p);
	FFT(b, a, 8, 1, p);
	for(i = 0; i < 8; i++) a[i] *= c[i];
	FFT(a, b, 8, -1, p);

	i = 0;
	for(int x : {15, 34, 26, 64, 55, 19, 42, 0})
		EXPECT_DOUBLE_EQ(x, b[i++].real());
}

TEST(FFT, Simple2) {
	a[0] = 111; a[1] = 222; a[2] = a[3] = 0;
	b[0] = 333; b[1] = 444; b[2] = b[3] = 0;
	FFT(a, c, 4, 1, p);
	EXPECT_EQ(c[0].real(), 333); // applied to 1
	EXPECT_EQ(c[2].real(),-111); // applied to -1
	FFT(b, a, 4, 1, p);
	EXPECT_EQ(a[0].real(), 777); // applied to 1
	EXPECT_EQ(a[2].real(),-111); // applied to -1
	for(int i = 0; i < 4; i++) a[i] = (a[i] * c[i] + 7. * a[i]);
	FFT(a, b, 4, -1, p);
	int i = 0;
	for(int x : {333 * 118, 222 * 333 + 444 * 118, 222 * 444, 0})
		EXPECT_EQ(b[i++].real(), x);
}

double rnd() { return double(rand()) / (double(RAND_MAX) + 1.); }
int rnd(int l, int r) { return l + rnd() * (r - l + 1); }

TEST(FFT, RootsOfUnity) {
	for(int tt = 0; tt < 40; tt++) {
		int sz = rnd(500, 1000);
		for(int i = 0; i < sz; i++) a[i] = rnd() * 20. - 10.;
		while(sz & (sz - 1)) a[sz++] = 0;
		FFT(a, b, sz, 1, p);
		cpx r(cos(2. * pi / sz), sin(2. * pi / sz));
		cpx x = 1;
		for(int i = 0; i < sz; i++) {
			cpx ans = 0;
			cpx y = 1;
			for(int j = 0; j < sz; j++) {
				ans += y * a[j];
				y *= x;
			}
			EXPECT_NEAR(ans.real(), b[i].real(), 1e-8);
			EXPECT_NEAR(ans.imag(), b[i].imag(), 1e-8);
			x *= r;
		}
	}
}


vector<cpx> naive (const vector<cpx> & a, const vector<cpx> & b) {
	vector<cpx> c(a.size() + b.size() - 1, 0);

	for (unsigned int i = 0; i < a.size(); i++)
		for (unsigned int j = 0; j < b.size(); j++)
			c[i+j] += a[i] * b[j];
	return c;
}

TEST(FFT, ComplexCoeficients) {
	mt19937_64 gen(42);
	uniform_int_distribution<int> rnd_size(3, 1000);
	uniform_real_distribution<double> rnd_value(-10, 10);

	int tc = 70;
	while (tc--) {
		vector<cpx> a(rnd_size(gen)), b(rnd_size(gen));

		for (unsigned int i = 0; i < a.size(); i++)
			a[i] = cpx(rnd_value(gen), rnd_value(gen));
		for (unsigned int i = 0; i < b.size(); i++)
			b[i] = cpx(rnd_value(gen), rnd_value(gen));

		vector<cpx> c = naive(a,b);
		int n = a.size() + b.size();
		while(n & (n - 1)) n++;
		a.resize(n, 0);
		b.resize(n, 0);
		FFT(a.data(), ::a, n, 1, p);
		FFT(b.data(), ::b, n, 1, p);
		for(int i = 0; i < n; i++)
			::a[i] *= ::b[i];
		FFT(::a, ::b, n, -1, p);
		c.resize(n, 0);

		for (int i = 0; i < n; i++) {
			EXPECT_NEAR(::b[i].real(), c[i].real(), 1e-9);
			EXPECT_NEAR(::b[i].imag(), c[i].imag(), 1e-9);
		}
	}
}
