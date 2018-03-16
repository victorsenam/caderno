#include <bits/stdc++.h>
using namespace std;
#include "gtest/gtest.h"
typedef long long num;
#include "../code/zeta.cpp"

const int N = 1 << 15;

num a[N], b[N], c[N], ans[N];

void apply(int n) {
	tf(a, 0, n - 1);
	tf(b, 0, n - 1);
	for(int i = 0; i < n; i++)
		c[i] = a[i] * b[i];
	itf(c, 0, n - 1);
}

TEST(Zeta, Simple) {
	a[0] = 1; a[1] = 1;
	b[0] = 1; b[1] = 1;
	apply(1 << 1);
	EXPECT_EQ(c[0], 1);
	EXPECT_EQ(c[1], 3);
}

TEST(Zeta, Random) {
	for(int t = 1; t <= 10; t++) {
		for(int i = 0; i < (1 << 12); i++) {
			a[i] = rand() % 100000;
			b[i] = rand() % 100000;
			ans[i] = 0;
		}
		for(int i = 0; i < (1 << 12); i++)
			for(int j = 0; j < (1 << 12); j++)
				ans[i | j] += a[i] * b[j];
		apply(1 << 12);
		for(int i = 0; i < (1 << 12); i++)
			EXPECT_EQ(ans[i], c[i]);
	}
}
