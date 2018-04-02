// gtest + pb_ds namespace collision fix
#define GTEST_HAS_TR1_TUPLE 0
#define GTEST_USE_OWN_TR1_TUPLE 0

#include "gtest/gtest.h"
#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

#include "../code/orderedset.cpp"

TEST(OrderedSet, NullType) {
	ord_set<int,null_type> s;
	s.insert(3);
	s.insert(5);
	EXPECT_EQ(*s.find_by_order(0), 3);
	EXPECT_EQ(s.find_by_order(2), s.end());
	EXPECT_EQ(s.order_of_key(2),0);
	EXPECT_EQ(s.order_of_key(3),0);
	EXPECT_EQ(s.order_of_key(4),1);
	EXPECT_EQ(s.order_of_key(6),2);
	s.erase(5);
	EXPECT_EQ(s.order_of_key(6),1);
}

TEST(OrderedSet, Map) {
	ord_set<int,ll> s;
	s[3] = 4;
	EXPECT_EQ(s.find_by_order(0)->first, 3);
	EXPECT_EQ(s.find_by_order(0)->second, 4);
	s[3] = 5;
	EXPECT_EQ(s.size(), 1) << "overwrites";
	EXPECT_EQ(s.find_by_order(0)->first, 3);
	EXPECT_EQ(s.find_by_order(0)->second, 5);
}
