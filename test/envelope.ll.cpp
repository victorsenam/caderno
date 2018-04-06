#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll num; const num eps = 0; num INF = 1e17;

#include "gtest/gtest.h"
#include "../code/envelope.cpp"

bool operator== (line a, line b) {
	return a.a == b.a && a.b == b.b;
}

template<typename line> bool operator== (const envelope<line> & a, const envelope<line> & b) {
	return a.lo == b.lo && a.hi == b.hi && a.q == b.q;
}

ostream & operator<< (ostream & os, line a) { return os << "(" << a.a << "x + " << a.b << ")"; }
ostream & operator<< (ostream & os, generic_line a) { return os << "(" << a.a << "x + " << a.b << ")"; }

template<typename line> ostream & operator<< (ostream & os, envelope<line> e) {
	os << "(";
	for (unsigned int i = 0; i < e.q.size(); i++) {
		if (i)
			os << " ";
		os << e.q[i];
	}
	return os << ")[" << e.lo << ".." << e.hi << "]";
}

TEST(line, inter) {
	num lo = -10, hi = 10;

	EXPECT_EQ(line({7,3}).inter({2,14}, lo, hi), 3) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(line({7,14}).inter({2,3}, lo, hi), -2) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(line({8,2}).inter({4,0}, lo, hi), 0) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(line({8,0}).inter({4,0}, lo, hi), 1) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(line({8,16}).inter({4,-16}, lo, hi), -7) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(line({8,-16}).inter({4,16}, lo, hi), 9) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(line({4213,321}).inter({324,2442}, lo, hi), 1) << "Should return floor of line intersection + 1 on simple cases.";

	EXPECT_EQ(line({1,3}).inter({1,2}, lo, hi), lo) << "Should return lo with parallels where b beats a.";
	EXPECT_EQ(line({1,2}).inter({1,3}, lo, hi), hi+1) << "Should return hi+1 with parallels where a beats b.";

	EXPECT_EQ(line({1,3}).inter({1,2}, lo, hi), lo) << "Should return -INF with parallels where b beats a.";
	EXPECT_EQ(line({1,2}).inter({1,3}, lo, hi), hi+1) << "Should return INF with parallels where a beats b.";
}

TEST(generic_line, inter) {
	num lo = -10, hi = 10;

	EXPECT_EQ(generic_line({7,3}).inter({2,14}, lo, hi), 3) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(generic_line({7,14}).inter({2,3}, lo, hi), -2) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(generic_line({8,2}).inter({4,0}, lo, hi), 0) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(generic_line({8,0}).inter({4,0}, lo, hi), 1) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(generic_line({8,16}).inter({4,-16}, lo, hi), -7) << "Should return floor of line intersection + 1 on simple cases.";
	EXPECT_EQ(generic_line({8,-16}).inter({4,16}, lo, hi), 9) << "Should return floor of line intersection + 1 on simple cases.";

	EXPECT_EQ(generic_line({1,3}).inter({1,2}, lo, hi), lo) << "Should return lo with parallels where b beats a.";
	EXPECT_EQ(generic_line({1,2}).inter({1,3}, lo, hi), hi+1) << "Should return hi+1 with parallels where a beats b.";

	EXPECT_EQ(generic_line({2,10000}).inter({-2,0}, lo, hi), lo) << "Should return lo when b beats a everywhere in range.";
	EXPECT_EQ(generic_line({2,0}).inter({-2,1000}, lo, hi), hi+1) << "Should return hi+1 when a beats b everywhere in range.";
}

TEST(envelope, Behaviour) {
	envelope<line> env[2] = { envelope<line>(-100,100), envelope<line>(-100,100) };

	// basic
	env[0].push_back({10,5});
	EXPECT_EQ(env[0].q.size(), 1) << "push_back should add first line.";
	env[1].push_front({9,-3});
	EXPECT_EQ(env[1].q.size(), 1) << "push_front should add first line.";

	env[0].push_back({9,-3});
	EXPECT_EQ(env[0].q.size(), 2) << "push_back should add intersecting line.";
	EXPECT_EQ(env[0].q.back(), line({9,-3})) << "push_back should add to the back.";
	env[1].push_front({10,5});
	EXPECT_EQ(env[1].q.size(), 2) << "push_front should add intersecting line.";
	EXPECT_EQ(env[1].q.front(), line({10,5})) << "push_front should add to the front.";
	EXPECT_EQ(env[0], env[1]) << "at this point operations made should be equivalent.";

	env[0].pop_back(100);
	EXPECT_EQ(env[0].q.back(), line({9,-3})) << "pop_back should answer min envelope value.";
	EXPECT_EQ(env[0].hi, 100) << "pop_back on hi should not change hi.";
	env[0].pop_front(-100);
	EXPECT_EQ(env[0].q.front(), line({10,5})) << "pop_front should answer min envelope value.";
	EXPECT_EQ(env[0].lo, -100) << "pop_front on lo should not change lo.";
	EXPECT_EQ(env[0], env[1]) << "trivial pops should not alter deque.";

	env[0].push_back({7,-4});
	EXPECT_EQ(env[0].q.size(), 3) << "push_back should add intersecting line.";
	EXPECT_EQ(env[0].q.back(), line({7,-4})) << "push_back should add to the back.";

	// parallels
	env[0].push_back({7,-3});
	EXPECT_EQ(env[0].q.size(), 3) << "push_back should ignore some parallel line.";
	EXPECT_EQ(env[0].q.back(), line({7,-4})) << "push_back should keep best parallel line.";

	env[0].push_back({7,-5});
	EXPECT_EQ(env[0].q.size(), 3) << "push_back should ignore some parallel line.";
	EXPECT_EQ(env[0].q.back(), line({7,-5})) << "push_back should remove worst parallel line.";

	env[1].push_back({7,-5});
	ASSERT_EQ(env[0], env[1]) << "old useless parallels are irrelevant.";

	env[1].push_front({10, 4});
	EXPECT_EQ(env[1].q.size(), 3) << "push_front should ignore some parallel line.";
	EXPECT_EQ(env[1].q.front(), line({10,4})) << "push_front should remove worst parallel line.";

	env[1].push_front({10, 6});
	EXPECT_EQ(env[1].q.size(), 3) << "push_front should ignore some parallel line.";
	EXPECT_EQ(env[1].q.front(), line({10,4})) << "push_front should keep best parallel line.";

	env[0].push_front({10, 4});
	EXPECT_EQ(env[0], env[1]) << "mixing push_back and push_front should be ok, adding parallels should be irrelevant.";

	// useless
	env[0].push_back({0,9});
	EXPECT_EQ(env[0].q.size(), 4) << "push_back should add another line.";

	env[0].push_back({-1,10});
	EXPECT_EQ(env[0].q.size(), 4) << "push_back should remove useless line.";
	EXPECT_EQ(env[0].q.back(), line({-1,10})) << "push_back should remove useless line.";

	env[1].push_back({-1,10});
	EXPECT_EQ(env[0], env[1]) << "adding useless lines should be irrelevant.";

	// out of bounds
	env[0].push_back({-2,10000});
	EXPECT_EQ(env[0].q.size(), 4) << "lines only useful out of bounds should be ignored.";
	EXPECT_EQ(env[0], env[1]) << "lines only useful out of bounds should be ignored.";
	env[0].push_front({90,11000});
	EXPECT_EQ(env[0].q.size(), 4) << "lines only useful out of bounds should be ignored.";
	EXPECT_EQ(env[0], env[1]) << "lines only useful out of bounds should be ignored.";

	// pops
	env[0].pop_back(1);
	EXPECT_EQ(env[0].q.back(), line({7,-5})) << "pop_back should return correct line.";
	EXPECT_EQ(env[0].hi, 1) << "pop_back should move bound.";
	EXPECT_EQ(env[0].q.size(), 3) << "pop_back should remove useless lines.";

	env[1].pop_front(0);
	EXPECT_EQ(env[1].q.front(), line({7,-5})) << "pop_front should return correct line.";
	EXPECT_EQ(env[1].lo, 0) << "pop_front should move bound.";
	EXPECT_EQ(env[1].q.size(), 2) << "pop_front should remove useless lines.";

	env[0].pop_front(-90);
	EXPECT_EQ(env[0].q.front(), line({10,4})) << "pop_front should return correct line.";
	EXPECT_EQ(env[0].lo, -90) << "pop_front should move bound.";
	EXPECT_EQ(env[0].q.size(), 3) << "pop_front should not remove lines unless necessary.";

	env[0].pop_front(0);
	EXPECT_EQ(env[0].q.front(), line({7,-5})) << "mixing pop_front and pop_back should be ok.";
	EXPECT_EQ(env[0].lo, 0) << "pop_front should move bound.";

	env[1].pop_back(1);
	EXPECT_EQ(env[1].q.back(), line({7,-5})) << "mixing pop_front and pop_back should be ok.";
	EXPECT_EQ(env[1].hi, 1) << "pop_back should move bound.";

	EXPECT_EQ(env[0], env[1]) << "mixing pop_front and pop_back should be ok.";

	env[0].push_front({7,-6});
	EXPECT_EQ(env[0].q.size(), 1) << "push_front should accept globally best.";
	env[1].push_back({7,-6});
	EXPECT_EQ(env[1].q.size(), 1) << "push_back should accept globally best.";

	EXPECT_EQ(env[0],env[1]) << "push_front and push_back with globally best and same slope should result in equality.";
}

TEST(line, InterRandom) {
	unsigned int x = time(NULL);
	cout << "Seed " << x << endl;
	srand(x); rand(); rand();
	int ts = 1e6, p_lim = 1e8;
	while (ts--) {
		num lo = -p_lim + (rand()%200), hi = p_lim - (rand()%200);
		line a({(rand()%(p_lim+p_lim+1)) - p_lim, (rand()%(p_lim+p_lim+1)) - p_lim});
		line b({(rand()%(p_lim+p_lim+1)) - p_lim, (rand()%(p_lim+p_lim+1)) - p_lim});
		if (b.a > a.a) swap(a,b);
		generic_line ga({a.a,a.b});
		generic_line gb({b.a,b.b});
		EXPECT_EQ(a.inter(b,lo,hi), ga.inter(gb,lo,hi));
	};
}

TEST(full_envelope, Random) {
	unsigned int x = time(NULL);
	cout << "Seed " << x << endl;
	srand(x); rand(); rand();
	int ts = 50, p_lim = 1e5;
	while (ts--) {
		int lo = -p_lim + (rand()%200);
		int hi = p_lim - (rand()%200);
		full_envelope<line> ev(envelope<line>(lo,hi));
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
