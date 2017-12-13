#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll cood;
const cood eps = 0;

#include "gtest/gtest.h"
#include "../../code/geometry/basic.cpp"

bool operator == (vec a, vec b)
{ return a.x == b.x && a.y == b.y; }

TEST(geometry_basic, vec) {
	vec a{45,16}, b{50,13};
	ll c = 10;

	EXPECT_EQ(a.x, 45);
	EXPECT_EQ(a.y, 16);

	EXPECT_EQ(a-b, vec({-5,3}));
	EXPECT_EQ(a+b, vec({95,29}));
	EXPECT_EQ(a*c, vec({450,160}));
	EXPECT_EQ(a/c, vec({4,1}));
	EXPECT_EQ(a^b, -215);
	EXPECT_EQ(a*b, 2458);
}
