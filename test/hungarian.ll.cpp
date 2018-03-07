#include <bits/stdc++.h>
using namespace std;
typedef long long num;
const int N = 112;
#include "gtest/gtest.h"
#include "../code/hungarian.cpp"

TEST(Hungarian, Simple) {
	hungarian h;
	h.n = 1;
	h.c[0][0] = 2;
	EXPECT_EQ(h.min_match(), 2);
	h.n = 2;
	h.c[0][0] = 2;
	h.c[1][1] = 2;
	h.c[0][1] = 1;
	h.c[1][0] = 1;
	EXPECT_EQ(h.min_match(), 2);
	EXPECT_EQ(h.MA[0], 1);
	EXPECT_EQ(h.MA[1], 0);
	h.c[0][0] = -2;
	EXPECT_EQ(h.min_match(), 0);
	EXPECT_EQ(h.MA[0], 0);
	EXPECT_EQ(h.MA[1], 1);
}
