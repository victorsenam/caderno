#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood;
const cood eps = 1e-8;
cood test_eps = eps;

#include "gtest/gtest.h"
#include "../../code/geometry/3d.cpp"

ostream& operator<<(ostream& os, pnt o) { return os << "(" << o.x << " " << o.y << " " << o.z << ")"; }

bool operator == (pnt a, pnt b) { return a.sq(b) <= test_eps; }

TEST(geometry_basic, basic_ops) {
	// Using 2 points precision only for simplicity
	test_eps = 1e-2;
	pnt a(2,3,1), b(-4,-1,5), c(-5,1,2), d(-2,1,4);
	EXPECT_EQ(a-b, pnt(6,4,-4));
	EXPECT_EQ(a+b, pnt(-2,2,6));
	EXPECT_EQ(a*2, pnt(4,6,2));
	EXPECT_EQ(a/2, pnt(1,1.5,0.5));
	EXPECT_DOUBLE_EQ(a*b, -6);
	EXPECT_EQ(a^b, pnt(16,-14,10));
	EXPECT_DOUBLE_EQ(a(b,c), -74);

	EXPECT_DOUBLE_EQ(a.inner(b,c), 54);
	EXPECT_EQ(a.cross(b,c), pnt(4,-22,-16));
	EXPECT_DOUBLE_EQ(a.mixed(b,c,d), -20);

	EXPECT_EQ(a.sq(b), 68);
	EXPECT_EQ(a.nr(c), 7.35);
	EXPECT_EQ((~a).nr(), 1);
	EXPECT_EQ((~c), pnt(-0.91, 0.18, 0.36));

	EXPECT_FALSE(c.in_seg(a,b));
	EXPECT_FALSE((a+b).in_seg(a,b));
	EXPECT_TRUE(((a+b)/2).in_seg(a,b));
	EXPECT_TRUE(((b+c+c)/3).in_seg(b,c));
	EXPECT_TRUE(a.in_seg(a,b));

	EXPECT_FALSE(d.in_tri(a,b,c));
	EXPECT_TRUE(((a+b)/2).in_tri(a,b,c));
	EXPECT_TRUE(((a+b+c)/3).in_tri(a,b,c));
	EXPECT_FALSE((a+b).in_tri(a,b,c));
	EXPECT_TRUE(a.in_tri(a,b,c));

	EXPECT_EQ(c.proj(a,b), pnt(-2.76,-0.18, 4.18));
	EXPECT_EQ(b.proj(c,a), c);
	EXPECT_EQ(b.proj(d,a), pnt(-4.07,-0.03, 5.55));

	EXPECT_NEAR(b.dist2_lin(a,d), 1.24, test_eps);
	EXPECT_DOUBLE_EQ(b.dist2_seg(a,d), b.sq(d));
	EXPECT_NEAR(d.dist2_lin(a,b), 0.53, test_eps);
	EXPECT_DOUBLE_EQ(d.dist2_lin(a,b), d.dist2_seg(a,d));

	EXPECT_NEAR(d.dist2_tri(a,b,c), 0.53, test_eps);
	EXPECT_DOUBLE_EQ(d.dist2_pln(a,b,c), d.dist2_tri(a,b,c));
	EXPECT_DOUBLE_EQ(b.dist2_tri(a,b,d), b.dist2_seg(d,c));
	EXPECT_NEAR(b.dist2_pln(a,b,c), 1.17, test_eps);
	EXPECT_NEAR(b.dist2_tri(a,b,c), 7.77, test_eps);

	EXPECT_NEAR(area(a,c,d), 9.23, test_eps);
	EXPECT_NEAR(area(a,b,c), 13.75, test_eps);
	EXPECT_DOUBLE_EQ(vol(a,b,c,d), 10/3.);

	EXPECT_EQ(inter_lin_pln(d,pnt(-4,5,-1),a,b,c), pnt(2,-5,12));
	EXPECT_EQ(inter_lin_pln(d,pnt(2,-6,-10),a,b,c), pnt(-1.8,0.64,3.29));

	// resetting test_eps
	test_eps = eps;
}
