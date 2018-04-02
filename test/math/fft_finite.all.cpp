#include "gtest/gtest.h"
#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back
const int N = 112345;
typedef ll num;
#include "../../code/math/fft_finite.cpp"

num a[N], b[N], c[N], w[N];
int pr[N];

vector<ll> naive (vector<ll> & a, vector<ll> & b, ll p) {
	vector<ll> c(a.size() + b.size(), 0);
	for (unsigned int i = 0; i < a.size(); i++) {
		for (unsigned int j = 0; j < b.size(); j++)
			c[i+j] = (c[i+j] + (a[i]*b[j])%p)%p;
	}
	return c;
}

TEST(fft_finite, Simple) {
	ll n = 8;
	ll p = 17;
	int i;
	i = 0; for (int x : {3,0,2,0}) a[i++] = x;
	i = 0; for (int x : {0,1,0,0}) b[i++] = x;
	for (i = n/2; i < n; i++) a[i] = b[i] = 0;

	fft_finite(a, c, n, 1, p, pr, w);
	i = 0; for (int x : {5,12,1,11,5,12,1,11}) EXPECT_EQ(c[i++],x);
	fft_finite(b, a, n, 1, p, pr, w);
	for (int i = 0; i < n; i++) a[i] = (a[i]*c[i])%p;
	fft_finite(a, b, n, -1, p, pr, w);
	i = 0; for (int x : {0,3,0,2,0,0,0,0}) EXPECT_EQ(b[i++],x);
}

TEST(fft_finite, SmallRandom) {
	mt19937_64 gen(42);
	vector<ll> primes({ 17,1009 });
	uniform_int_distribution<int> rnd_prime(0,primes.size()-1);

	int tc = 70;
	while (tc--) {
		ll p = primes[rnd_prime(gen)];
		ll n = 2;
		while ((p-1)%(n+n) == 0) n += n;
		n /= 2;

		uniform_int_distribution<int> rnd_val(0,p-1);
		vector<ll> a(n), b(n);
		for (int i = 0; i < n; i++) a[i] = rnd_val(gen);
		for (int i = 0; i < n; i++) b[i] = rnd_val(gen);
		vector<ll> c = naive(a,b,p);

		n += n;
		assert(c.size() == unsigned(n));
		a.resize(n,0); b.resize(n,0);
		fft_finite(a.data(), ::a, n, 1, p, pr, w);
		fft_finite(b.data(), ::b, n, 1, p, pr, w);
		for (int i = 0; i < n; i++) ::a[i] = (::a[i]*::b[i])%p;
		fft_finite(::a, ::b, n, -1, p, pr, w);
		
		for (int i = 0; i < n; i++)
			EXPECT_EQ(::b[i], c[i]) << i << "-th element differ";
	}
}
