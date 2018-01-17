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

bool operator== (cir a, cir b)
{ return (a.c == b.c && abs(a.r - b.r) <= eps); }
bool operator!= (cir a, cir b)
{ return !(a==b); }
::std::ostream& operator<<(::std::ostream& os, const vector<vec> & v) {
	for (int i = 0; i < (int) v.size(); i++)
		os << (i?",":"{") << v[i];
	return os << "}";
}

::testing::AssertionResult contained (vec * v, int n, cir c) {
	for (int i = 0; i < n; i++)
		if (!c.contains(v[i])) return ::testing::AssertionFailure() << "circle " << c << " doesn't contain " << v[i];
	return ::testing::AssertionSuccess();
}

::testing::AssertionResult is_msc (vec * v, int n, cir c) {
	::testing::AssertionResult ret = contained(v,n,c);
	if (!ret) return ret;

	for (int i = 0; i < n; i++) {
		cir d(v[i],0);
		if (d.r < c.r && contained(v,n,d)) return ::testing::AssertionFailure() << "circle " << d << " is better than " << c;
		for (int j = 0; j < i; j++) {
			cir d((v[i]+v[j])/2,v[i].nr(v[j])/2);
			if (d.r < c.r && contained(v,n,d)) return ::testing::AssertionFailure() << "circle " << d << " is better than " << c;
			for (int k = 0; k < j; k++) {
				if (v[i].ccw(v[j],v[k]) == 0) continue;
				cir d(v[i],v[j],v[k]);
				if (d.r < c.r && contained(v,n,d)) return ::testing::AssertionFailure() << "circle " << d << " is better than " << c;
			}
		}
	}
	return ::testing::AssertionSuccess();
}

::testing::AssertionResult test_msc (vec * v, int n, int ts = 10) {
	cir c = min_spanning_circle(v,n);
	::testing::AssertionResult ret = is_msc(v,n,c);
	vector<vec> snap(v, v+n);
	if (!ret) return ret << " with " << snap;

	for (int t = 0; t < ts; t++) {
		cir d = min_spanning_circle(v,n);
		if (c != d)
			return ::testing::AssertionFailure() << "different circles:\n" << c << " with " << snap << "\n" << d << " with " << vector<vec>(v,v+n);
	}
	return ::testing::AssertionSuccess();
}

TEST(geometry_algorithms, min_spanning_circle) {
	vector<vec> A({vec(-6,8), vec(-2,6), vec(-6,4), vec(-2,10), vec(-8,6), vec(-4,2)});
	// note os 3 pontos colineares na entrada (2,4,5)
	EXPECT_TRUE(test_msc(&A[0],6));
	EXPECT_TRUE(test_msc(&A[0],3));
	for (int t = 0; t < 4; t++) {
		random_shuffle(A.begin(),A.end());
		EXPECT_TRUE(test_msc(&A[0],3));
	}
}
