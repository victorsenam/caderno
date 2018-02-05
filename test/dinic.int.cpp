const int N = 112345;
const int M = 112345 * 2;
typedef int num;

#include <bits/stdc++.h>
using namespace std;
#include "gtest/gtest.h"
#include "../code/dinic.cpp"

dinic d;

TEST(Dinic, Sum) {
	d.reset(2);
	d.add_edge(0, 1, 7);
	d.add_edge(0, 1, 12);
	EXPECT_EQ(d.max_flow(0, 1), 19) << "Parallel edges should work";
	d.reset_flow();
	EXPECT_EQ(d.max_flow(1, 0), 0) << "Reverse edges with 0 capacity";
}

TEST(Dinic, Min) {
	d.reset(3);
	d.add_edge(0, 1, 12);
	d.add_edge(1, 2, 7);
	EXPECT_EQ(d.max_flow(0, 2), 7) << "Min not working";
	d.add_edge(1, 2, 2);
	EXPECT_EQ(d.max_flow(0, 2), 2) << "Aditional flow not working";
	d.reset_flow();
	EXPECT_EQ(d.max_flow(0, 2), 9);
}
