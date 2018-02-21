#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll num; const num eps = 0;

#include "gtest/gtest.h"
#include "../code/envelope.cpp"

bool operator== (line a, line b) {
	return a.a == b.a && a.b == b.b;
}

bool operator== (const envelope & a, const envelope & b) {
	return a.qu == b.qu && a.lo == b.lo && a.hi == b.hi;
}

ostream & operator<< (ostream & os, line a) {
	return os << "(" << a.a << "x + " << a.b << ")";
}

ostream & operator<< (ostream & os, envelope e) {
	os << "(";
	for (unsigned int i = 0; i < e.qu.size(); i++) {
		if (i)
			os << " ";
		os << e.qu[i];
	}
	return os << ")[" << e.lo << ".." << e.hi << "]";
}

TEST(EnvelopeInter, Simple) {
	envelope env(-1e9,1e9);

	EXPECT_EQ(env.inter({7,3},{2,14}), 3) << "Should return ceil of line intersection on simple cases.";
	EXPECT_EQ(env.inter({7,14},{2,3}), -2) << "Should return ceil of line intersection on simple cases.";
	EXPECT_EQ(env.inter({4213,321},{324,2442}), 1) << "Should return ceil of line intersection on simple cases.";
}

TEST(EnvelopeInter, Parallels) {
	envelope env(-1e9,1e9);

	EXPECT_EQ(env.inter({1,3},{1,2}), env.lo) << "Should return lo with parallels where b beats a.";
	EXPECT_EQ(env.inter({1,2},{1,3}), env.hi+1) << "Should return hi+1 with parallels where a beats b.";
}

TEST(EnvelopeInter, LowRange) {
	envelope env(-10,10);

	EXPECT_EQ(env.inter({2,10000},{-2,0}), env.lo) << "Should return lo when b beats a everywhere in range.";
	EXPECT_EQ(env.inter({2,0},{-2,1000}), env.hi+1) << "Should return hi+1 when a beats b everywhere in range.";
}

TEST(Envelope, Simple) {
	envelope env[2] = { envelope(-100,100), envelope(-100,100) };

	// basic
	env[0].push_back({10,5});
	EXPECT_EQ(env[0].qu.size(), 1) << "push_back should add first line.";
	env[1].push_front({9,-3});
	EXPECT_EQ(env[1].qu.size(), 1) << "push_front should add first line.";

	env[0].push_back({9,-3});
	env[1].push_front({10,5});
	EXPECT_EQ(env[0].qu.size(), 2) << "push_back should add intersecting line.";
	EXPECT_EQ(env[0].qu.back(), line({9,-3})) << "push_back should add to the back.";
	EXPECT_EQ(env[1].qu.size(), 2) << "push_front should add intersecting line.";
	EXPECT_EQ(env[0].qu.front(), line({10,5})) << "push_front should add to the front.";
	EXPECT_EQ(env[0], env[1]) << "at this point operations made should be equivalent.";


	EXPECT_EQ(env[0].pop_back(100), line({9,-3})) << "pop_back should answer min envelope value.";
	EXPECT_EQ(env[0].pop_front(-100), line({10,5})) << "pop_front should answer min envelope value.";
	EXPECT_EQ(env[0].hi, 100) << "pop_back on hi should not change hi.";
	EXPECT_EQ(env[0].lo, -100) << "pop_front on lo should not change lo.";
	EXPECT_EQ(env[0], env[1]) << "trivial pops should not alter deque.";

	env[0].push_back({7,-4});
	EXPECT_EQ(env[0].qu.size(), 3) << "push_back should add intersecting line.";
	EXPECT_EQ(env[0].qu.back(), line({7,-4})) << "push_back should add to the back.";

	// parallels
	env[0].push_back({7,-3});
	EXPECT_EQ(env[0].qu.size(), 3) << "push_back should ignore some parallel line.";
	EXPECT_EQ(env[0].qu.back(), line({7,-4})) << "push_back should keep best parallel line.";

	env[0].push_back({7,-5});
	EXPECT_EQ(env[0].qu.size(), 3) << "push_back should ignore some parallel line.";
	EXPECT_EQ(env[0].qu.back(), line({7,-5})) << "push_back should remove worst parallel line.";

	env[1].push_back({7,-5});
	EXPECT_EQ(env[0], env[1]) << "mixing push_back and push_front should be ok, adding parallels should be irrelevant.";

	env[1].push_front({10, 4});
	EXPECT_EQ(env[1].qu.size(), 3) << "push_front should ignore some parallel line.";
	EXPECT_EQ(env[1].qu.front(), line({10,4})) << "push_front should remove worst parallel line.";

	env[1].push_front({10, 6});
	EXPECT_EQ(env[1].qu.size(), 3) << "push_front should ignore some parallel line.";
	EXPECT_EQ(env[1].qu.front(), line({10,4})) << "push_front should keep best parallel line.";

	env[0].push_front({10,4});
	EXPECT_EQ(env[0], env[1]) << "mixing push_back and push_front should be ok, adding parallels should be irrelevant.";

	// useless
	env[0].push_back({0,9});
	EXPECT_EQ(env[0].qu.size(), 4) << "push_back should add another line.";

	env[0].push_back({-1,10});
	EXPECT_EQ(env[0].qu.size(), 4) << "push_back should remove useless line.";
	EXPECT_EQ(env[0].qu.back(), line({-1,10})) << "push_back should remove useless line.";

	env[1].push_back({-1,10});
	EXPECT_EQ(env[0], env[1]) << "adding useless lines should be irrelevant.";

	// out of bounds
	env[0].push_back({-2,10000});
	EXPECT_EQ(env[0].qu.size(), 4) << "lines only useful out of bounds should be ignored.";
	EXPECT_EQ(env[0], env[1]) << "lines only useful out of bounds should be ignored.";
	env[0].push_front({90,11000});
	EXPECT_EQ(env[0].qu.size(), 4) << "lines only useful out of bounds should be ignored.";
	EXPECT_EQ(env[0], env[1]) << "lines only useful out of bounds should be ignored.";

	// pops
	EXPECT_EQ(env[0].pop_back(1), line({7,-5})) << "pop_back should return correct line.";
	EXPECT_EQ(env[0].hi, 1) << "pop_back should move bound.";
	EXPECT_EQ(env[0].qu.size(), 3) << "pop_back should remove useless lines.";

	EXPECT_EQ(env[1].pop_front(0), line({7,-5})) << "pop_front should return correct line.";
	EXPECT_EQ(env[1].lo, 0) << "pop_front should move bound.";
	EXPECT_EQ(env[1].qu.size(), 2) << "pop_front should remove useless lines.";

	EXPECT_EQ(env[0].pop_front(-90), line({10,4})) << "pop_front should return correct line.";
	EXPECT_EQ(env[0].lo, -90) << "pop_front should move bound.";
	EXPECT_EQ(env[0].qu.size(), 3) << "pop_front should not remove lines unless necessary.";

	EXPECT_EQ(env[0].pop_front(0), line({7,-5})) << "mixing pop_front and pop_back should be ok.";
	EXPECT_EQ(env[0].lo, 0) << "pop_front should move bound.";

	EXPECT_EQ(env[1].pop_back(1), line({7,-5})) << "mixing pop_front and pop_back should be ok.";
	EXPECT_EQ(env[1].hi, 1) << "pop_back should move bound.";

	EXPECT_EQ(env[0], env[1]) << "mixing pop_front and pop_back should be ok.";

	env[0].push_front({7,-6});
	EXPECT_EQ(env[0].qu.size(), 1) << "push_front should accept globally best.";
	env[1].push_back({7,-6});
	EXPECT_EQ(env[1].qu.size(), 1) << "push_back should accept globally best.";

	EXPECT_EQ(env[0],env[1]) << "push_front and push_back with globally best and same slope should result in equality.";
}

TEST(FullEnvelope, Random) {
	srand(time(NULL)); rand(); rand();
	int ts = 50, p_lim = 1e5;
	while (ts--) {
		int lo = -p_lim + (rand()%200);
		int hi = p_lim - (rand()%200);
		full_envelope ev(envelope(lo,hi));
		int n = 900 + (rand()%200);
		vector<line> v;

		for (int i = 0; i < n; i++) {
			if (!i || rand()%10) {
				line cur({1000 - (rand()%2000), 1000 - (rand()%2000)});
				ev.add(cur);
				v.pb(cur);
			} else {
				int x = (rand()%(hi-lo+1)) + lo;
				ll res = ev.get(x)(x);
				ll cur = LLONG_MAX;
				for (line l : v)
					cur = min(cur, l(x));
				ASSERT_EQ(cur,res);
			}
		}
	}
}
