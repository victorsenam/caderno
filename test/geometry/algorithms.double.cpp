#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood;
const double eps = 1e-8;
const double inf = 1./0.;

#include "gtest/gtest.h"
#include "../../code/geometry/basic.cpp"
#include "../../code/geometry/algorithms.cpp"

bool operator== (vec a, vec b)
{ return (abs(a.x - b.x) < eps && abs(a.y - b.y) <= eps); }
bool operator== (cir a, cir b)
{ return (a.c == b.c && abs(a.r - b.r) <= eps); }
::std::ostream& operator<<(::std::ostream& os, const vector<vec> & v) {
	for (int i = 0; i < (int) v.size(); i++)
		os << (i?",":"{") << v[i];
	return os << "}";
}

::testing::AssertionResult is_msc (vector<vec> v, cir c) { 
	int border_cnt = 0;
	for (vec a : v) {
		if (!c.contains(a)) return ::testing::AssertionFailure() << "circle " << c << " doesn't contain " << a;
		if (abs(c.c.nr(a) - c.r) <= eps) border_cnt++;
	}

	if (border_cnt < 3)
		return ::testing::AssertionFailure() << "circle " << c << " only has " << border_cnt << " points in border";
	return ::testing::AssertionSuccess();
}

TEST(geometry_algorithms, min_spanning_circle) {
	vector<vec> A({vec(-6,8), vec(-2,6), vec(-6,4), vec(-2,10), vec(-8,6), vec(-4,2)});
	EXPECT_TRUE(is_msc(A,min_spanning_circle(A))) << min_spanning_circle(A) << " should be msc of " << A;

	A.resize(3);
	EXPECT_TRUE(is_msc(A,min_spanning_circle(A))) << min_spanning_circle(A) << " should be msc of " << A;
}
