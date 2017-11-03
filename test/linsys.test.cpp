const int N = 1123;
#include <bits/stdc++.h>
using namespace std;
#include "../code/linsys.cpp"
#include "gtest/gtest.h"

TEST(Simple, Identity) {
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
			a[i][j] = (i == j);
	for(int i = 0; i < 10; i++)
		a[i][10] = i;
	EXPECT_DOUBLE_EQ(1, solve(10));
	for(int i = 0; i < 10; i++)
		EXPECT_DOUBLE_EQ(ans[i], i);
}

TEST(Simple, Ex2) {
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
			a[i][j] = (i == j) * (i + 1);
	for(int i = 0; i < 10; i++)
		a[i][10] = (i + 1);
	EXPECT_DOUBLE_EQ(3628800, solve(10));
	for(int i = 0; i < 10; i++)
		EXPECT_DOUBLE_EQ(ans[i], 1);
}

double rnd() { return double(rand()) / (double(RAND_MAX) + 1.); }
double rnd(double l, double r) { return rnd() * (r - l) + l; }

double tmp[N];
void rand_case(int n, double l, double r, double ml, double mr) {
	for(int i = 0; i < n; i++)
		tmp[i] = rnd(l, r);
	for(int i = 0; i < n; i++) {
		a[i][n] = 0;
		for(int j = 0; j < n; j++) {
			a[i][j] = rnd(ml, mr);
			a[i][n] += a[i][j] * tmp[j];
		}
	}
	solve(n);
	for(int i = 0; i < n; i++)
		EXPECT_NEAR(ans[i], tmp[i], 1e-8);
}

TEST(Rand, Small) {
	for(int t = 0; t < 10; t++)
		rand_case(10, 0, 10, 0, 10);
	for(int t = 0; t < 10; t++)
		rand_case(20, -1000, 1000, -10, 10);
	for(int t = 0; t < 10; t++)
		rand_case(40, -1000, 1000, -1000, 1000);
}

TEST(Rand, Medium) {
	for(int t = 0; t < 10; t++)
		rand_case(100, 0, 10, 0, 10);
	for(int t = 0; t < 10; t++)
		rand_case(200, -1000, 1000, -10, 10);
	for(int t = 0; t < 10; t++)
		rand_case(300, -1000, 1000, -1000, 1000);
}

TEST(Rand, Large) {
	for(int t = 0; t < 4; t++)
		rand_case(500, 0, 10, 0, 10);
	for(int t = 0; t < 4; t++)
		rand_case(400, -1000, 1000, -10, 10);
	rand_case(900, -1000, 1000, -1000, 1000);
}
