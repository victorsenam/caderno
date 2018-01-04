#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll cood;
const cood eps = 0;
const cood inf = 1e15;

#include "gtest/gtest.h"
#include "../../code/geometry/basic.cpp"
#include "../../code/geometry/algorithms.cpp"

bool operator == (vec a, vec b)
{ return a.x == b.x && a.y == b.y; }
bool operator != (vec a, vec b)
{ return !(a==b); }


const vec sample_pointset[] = { vec(7,7), vec(8,7), vec(8,8), vec(10,7), vec(10,8), vec(11,7), vec(11,11), vec(11,9), vec(12,12), vec(13,9), vec(14,10), vec(14,9), vec(14,14), vec(15,14), vec(15,12), vec(15,11) };
const int sample_size = 16;

TEST(geometry, convex_hull) { 
	vector<vec> v(sample_pointset, sample_pointset+16);
	vector<vec> expect({ vec(15,11), vec(15,14), vec(14,14), vec(7,7), vec(11,7), vec(14,9) });
	EXPECT_EQ(convex_hull(v, 0), 6) << "Convex hull should have size 6";
	EXPECT_EQ(v,expect) << "simple";

	v = vector<vec>({ vec(0,0), vec(0,0) });
	expect = vector<vec>({ vec(0,0) });
	EXPECT_EQ(convex_hull(v, 0), 1) << "Repeated points should be irrelevant";
	EXPECT_EQ(v[0], vec(0,0)) << "repeated";

	v = vector<vec>(sample_pointset, sample_pointset+16);
	expect = vector<vec>({ vec(15,11), vec(15,12), vec(15,14), vec(14,14), vec(12,12), vec(11,11), vec(8,8), vec(7,7), vec(8,7), vec(10,7), vec(11,7), vec(14,9) });
		

	EXPECT_EQ(convex_hull(v, 1), 12) << "Convex hull should have size 12";
	EXPECT_EQ(v,expect) << "border in";
}

TEST(geometry, polygon_inter) {
	vector<vec> v({vec(3,4), vec(5, 2), vec(7, 3)});
	cir c(vec(3,4), 5);
	EXPECT_EQ(polygon_inter(v,c), c.triang_inter(v[1],v[2])) << "Same center inside";

	v[1] = vec(30,4); v[2] = vec(3,84);
	EXPECT_EQ(polygon_inter(v,c), c.arc_area(v[1],v[2])) << "Same center outside";

	c.c = vec(4,5);
	v.resize(2);
	EXPECT_NEAR(polygon_inter(v,c), 0., 1e-12) << "Degenerate";
}

TEST(geometry, polygon_pos) {
	// Geogebra: https://ggbm.at/BaFwEPXZ
	vector<vec> p({ vec(14,14), vec(20,8), vec(10,2), vec(2,12), vec(6,16), vec(10,16), vec(10,20), vec(6,22), vec(14,24), vec(14,26), vec(6,26), vec(19,31), vec(10,31), vec(6,33), vec(19,35), vec(10,35), vec(10,39), vec(5,39), vec(17,42), vec(10,45), vec(10,48), vec(13,50), vec(24,44) });

	EXPECT_EQ(polygon_pos(p, vec(10,10)), 1); // B_0
	EXPECT_EQ(polygon_pos(p, vec(10,18)), 0); // B_1
	EXPECT_EQ(polygon_pos(p, vec(10,22)), 1); // B_2
	EXPECT_EQ(polygon_pos(p, vec(10,25)), -1); // B_3
	EXPECT_EQ(polygon_pos(p, vec(10,27)), 1); // B_4
	EXPECT_EQ(polygon_pos(p, vec(10,29)), -1); // B_5
	EXPECT_EQ(polygon_pos(p, vec(10,32)), 1); // B_6
	EXPECT_EQ(polygon_pos(p, vec(10,34)), -1); // B_7
	EXPECT_EQ(polygon_pos(p, vec(10,36)), 0); // B_8
	EXPECT_EQ(polygon_pos(p, vec(10,40)), 1); // B_9
	EXPECT_EQ(polygon_pos(p, vec(13,41)), 0); // B_{10}
	EXPECT_EQ(polygon_pos(p, vec(14,14)), 0); // B_{11}
	EXPECT_EQ(polygon_pos(p, vec(10,20)), 0); // B_{12}
	EXPECT_EQ(polygon_pos(p, vec(19,33)), 1); // B_{13}
	EXPECT_EQ(polygon_pos(p, vec(5,13)), 1); // B_{14}
	EXPECT_EQ(polygon_pos(p, vec(5,18)), -1); // B_{15}
	EXPECT_EQ(polygon_pos(p, vec(6,12)), 1); // B_{16}
	EXPECT_EQ(polygon_pos(p, vec(10,-1)), -1); // B_{17}
	EXPECT_EQ(polygon_pos(p, vec(20,6)), -1); // B_{18}
	EXPECT_EQ(polygon_pos(p, vec(20,10)), -1); // B_{19}
	EXPECT_EQ(polygon_pos(p, vec(10,42)), -1); // B_{20}
	EXPECT_EQ(polygon_pos(p, vec(10,47)), 0); // B_{21}
	EXPECT_EQ(polygon_pos(p, vec(13,47)), 1); // B_{22}
	EXPECT_EQ(polygon_pos(p, vec(16,9)), 1); // B_{23}
	EXPECT_EQ(polygon_pos(p, vec(17,5)), -1); // B_{24}
}
