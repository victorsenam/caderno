const int N = 112345;
const int M = 112345 * 2;
typedef int num;
typedef int val;
const num eps = 0;

#include <bits/stdc++.h>
using namespace std;
#include "gtest/gtest.h"
#include "../code/cycle_cancel.cpp"

cycle_cancel d;

TEST(CycleCancel, Sum) {
	d.init(2);
	d.add_edge(0, 1, 7, 2);
	d.add_edge(0, 1, 12, 3);
	d.min_cost(0, 1);
	EXPECT_EQ(d.flow, 19) << "Parallel edges should work";
	EXPECT_EQ(d.tot, 7 * 2 + 12 * 3) << "Parallel edges should work";
	d.reset_flow();
	EXPECT_EQ(d.min_cost(1, 0), 0) << "Reverse edges with 0 capacity";
	EXPECT_EQ(d.flow, 0) << "Reverse edges with 0 capacity";
}

TEST(CycleCancel, Min) {
	d.init(3);
	d.add_edge(0, 1, 12, 10);
	d.add_edge(1, 2, 7, 1);
	EXPECT_EQ(d.min_cost(0, 2), 77) << "Min not working";
	EXPECT_EQ(d.flow, 7) << "Min not working";
	d.add_edge(1, 2, 2, 100);
	EXPECT_EQ(d.min_cost(0, 2), 297) << "Aditional flow not working";
	EXPECT_EQ(d.flow, 2) << "Aditional flow not working";
	d.reset_flow();
	EXPECT_EQ(d.min_cost(0, 2), 297);
	EXPECT_EQ(d.flow, 9);
}

TEST(CycleCancel, Flow0) {
	d.init(4);
	d.add_edge(0, 1, 100, -10);
	d.add_edge(1, 0, 10, -5);
	d.min_cost(2, 3);
	EXPECT_EQ(d.flow, 0);
	EXPECT_EQ(d.tot, -150);
}

TEST(CycleCancel, SimpleCirc) {
	d.init(4);
	d.add_edge(0, 1, 1, -1);
	d.add_edge(1, 0, 1, -1);
	d.min_cost(2, 3);
	EXPECT_EQ(d.flow, 0);
	EXPECT_EQ(d.tot, -2);
}

TEST(CycleCancel, Break) {
	d.init(6);
	d.add_edge(0, 1, 2, -3);
	d.add_edge(1, 0, 1, 1);
	d.add_edge(1, 2, 1, 0);
	d.add_edge(2, 3, 2, 0);
	d.add_edge(3, 0, 2, -2);
	d.add_edge(0, 2, 1, 3);
	d.min_cost(4, 5);
	EXPECT_EQ(d.flow, 0);
	EXPECT_EQ(d.tot, -7);
}
