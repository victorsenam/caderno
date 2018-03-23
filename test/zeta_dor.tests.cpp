#include <bits/stdc++.h>
using namespace std;
#include "gtest/gtest.h"
typedef long long num;
const int K = 15;
#include "../code/zeta_dor.cpp"

const int N = 1 << K;

num a[N], b[N], c[N];
num a_[K+1][1 << K], b_[K+1][1 << K], ans[K+1][1 << K];
num brute[N];

void apply(int k) {
	for(int i = 0; i < (1 << k); i++) {
		brute[i] = a[0] * b[i];
		for(int j = i; j; j = (j - 1) & i)
			brute[i] += a[j] * b[i ^ j];
	}
	tf(k, a, a_);
	tf(k, b, b_);
	conv(k, a_, b_, ans);
	itf(k, ans, c);
	for(int i = 0; i < (1 << k); i++)
		EXPECT_EQ(c[i], brute[i]);
}

TEST(ZetaDor, Simple) {
	a[0] = 1; a[1] = 1;
	b[0] = 1; b[1] = 1;
	apply(1);
	EXPECT_EQ(c[0], 1);
	EXPECT_EQ(c[1], 2);
	for(int i = 0; i < 4; i++)
		a[i] = b[i] = 1;
	apply(2);
	EXPECT_EQ(c[0], 1);
	EXPECT_EQ(c[1], 2);
	EXPECT_EQ(c[2], 2);
	EXPECT_EQ(c[3], 4);
}

TEST(ZetaDor, Random) {
	for(int t = 1; t <= 20; t++) {
		int k = min(t, K);
		for(int i = 0; i < (1 << k); i++) {
			a[i] = rand() % 100000;
			b[i] = rand() % 100000;
		}
		apply(k);
	}
}
