#include <bits/stdc++.h>
using namespace std;
#include "gtest/gtest.h"

const int N = 1000;
const int M = 1000;
typedef long double dbl;
#include "../code/simplex.cpp"

simplex s;

TEST(Simplex, Simple) {
	// just maximizing a number
	s.c[0] = 1;
	try {
		s.solve(1, 0);
		ADD_FAILURE();
	} catch(int x) {
		EXPECT_EQ(x, 2);
	}
	s.c[0] = 1;
	s.A[0][0] = 1;
	s.b[0] = 0; // x <= 0
	s.b[1] = -1;
	s.A[0][0] = -1; // -x <= -1
	try {
		s.solve(1, 2);
		ADD_FAILURE();
	} catch(int x) {
		EXPECT_EQ(x, 1);
	}
	s.c[0] = 5; // 5x
	s.A[0][0] = 2;
	s.b[0] = 3; // 2x <= 3
	EXPECT_DOUBLE_EQ(s.solve(1, 1), 7.5);
	EXPECT_DOUBLE_EQ(s.sol[0], 1.5);
}

typedef long long ll;

dbl rnd() {
	return dbl(ll(rand()) * ll(RAND_MAX) + ll(rand())) / dbl(ll(RAND_MAX) * ll(RAND_MAX));
}

dbl rnd(dbl l, dbl r) {
	return rnd() * (r - l) + l;
}

dbl A[M][N], c[N], b[M];

void go(int n, int m) {
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			A[i][j] = s.A[i][j] = rnd(-10, 10);
	for(int i = 0; i < n; i++) c[i] = s.c[i] = rnd(-10, 10);
	for(int i = 0; i < m; i++) b[i] = s.b[i] = rnd(-10, 100);
	try {
		dbl ans = s.solve(n, m);
		//printf("ans %.5f\n", double(ans));
		for(int i = 0; i < n; i++)
			EXPECT_GE(s.sol[i], -eps);
		for(int i = 0; i < m; i++) {
			dbl v = 0;
			for(int j = 0; j < n; j++)
				v += A[i][j] * s.sol[j];
			EXPECT_LE(v, b[i] + eps);
		}
		dbl v = 0;
		for(int i = 0; i < n; i++)
			v += c[i] * s.sol[i];
		EXPECT_DOUBLE_EQ(v, ans);
		for(int i = 0; i < n; i++)
			s.sol[i] += .01 * c[i];
		v = 0;
		for(int i = 0; i < n; i++)
			v += c[i] * s.sol[i];
		EXPECT_GT(v, ans);
		bool any = false;
		for(int i = 0; !any && i < n; i++)
			any = any || (s.sol[i] < -eps);
		for(int i = 0; !any && i < m; i++) {
			dbl v = 0;
			for(int j = 0; j < n; j++)
				v += A[i][j] * s.sol[j];
			if(v > b[i] + eps)
				any = true;
		}
		EXPECT_TRUE(any);
	} catch(int x) {
		//if(x == 1) puts("no solution");
		//else puts("unbounded");
	}
}

TEST(Simplex, ExistenceOk) {
	for(int t = 0; t < 5; t++) {
		go(5, 20);
		go(10, 100);
		go(30, 50);
	}
}
