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

ostream& operator<<(ostream& os, vec o) { return os << '(' << o.x << ", " << o.y << ')'; }
ostream& operator<<(ostream& os, lin o) { return os << '[' << o.p << "*(x,y) = " << o.c << ']'; }
ostream& operator<<(ostream& os, cir o) { return os << '[' << o.c << o.r << ']'; }

bool operator != (vec a, vec b)
{ return !(a==b); }

const vec sample_pointset[] = { vec(7,7), vec(8,7), vec(8,8), vec(10,7), vec(10,8), vec(11,7), vec(11,11), vec(11,9), vec(12,12), vec(13,9), vec(14,10), vec(14,9), vec(14,14), vec(15,14), vec(15,12), vec(15,11) };
const int sample_size = 16;

::testing::AssertionResult testConvex (vector<vec> points, vector<vec> expect, int in_border) {
	vector<vec> a = points; a.resize(convex_hull(&a[0],a.size(),in_border));
	if (expect.size() && a != expect) return ::testing::AssertionFailure() << "\ngiven " << ::testing::PrintToString(points) << "\nconvex_hull returns " << ::testing::PrintToString(a) << "\nexpect is " << ::testing::PrintToString(expect) << "\n";
	vector<vec> b = points; b.resize(monotone_chain(&b[0],b.size(),in_border));
	if (expect.size() && b != expect) return ::testing::AssertionFailure() << "\ngiven " << ::testing::PrintToString(points) << "\nmonotone_chain returns " << ::testing::PrintToString(b) << "\nexpect is " << ::testing::PrintToString(expect) << "\n";
	if (a != b) return ::testing::AssertionFailure() << "\ngiven " << ::testing::PrintToString(points) << "\nconvex_hull returns " << ::testing::PrintToString(a) << "\nmonotone_chain returns " << ::testing::PrintToString(b) << "\n";
	return ::testing::AssertionSuccess();
}

TEST(geometry, convex_hull) { 
	EXPECT_TRUE(testConvex(vector<vec>(sample_pointset,sample_pointset+16), { vec(7,7), vec(11,7), vec(14,9), vec(15,11), vec(15,14), vec(14,14) }, 0)) << "simple";
	EXPECT_TRUE(testConvex(vector<vec>(sample_pointset,sample_pointset+16), { vec(7,7), vec(8,7), vec(10,7), vec(11,7), vec(14,9), vec(15,11), vec(15,12), vec(15,14), vec(14,14), vec(12,12), vec(11,11), vec(8,8) }, 1)) << "border_in";

	EXPECT_TRUE(testConvex({ vec(0,0), vec(0,0) }, { vec(0,0) }, 0)) << "repeated";
	EXPECT_TRUE(testConvex({ vec(0,0), vec(0,0) }, { vec(0,0) }, 1)) << "repeated border_in";

	EXPECT_TRUE(testConvex({ vec(0,2), vec(0,1), vec(0,0), vec(1,0), vec(2,0), vec(2,1), vec(2,2), vec(1,2) }, { vec(0,2), vec(0,0), vec(2,0), vec(2,2) }, 0)) << "many border points";
	EXPECT_TRUE(testConvex({ vec(0,2), vec(0,1), vec(0,0), vec(1,0), vec(2,0), vec(2,1), vec(2,2), vec(1,2) }, { vec(0,2), vec(0,1), vec(0,0), vec(1,0), vec(2,0), vec(2,1), vec(2,2), vec(1,2) }, 1)) << "many border points border_in";
}

TEST(geometry, convex_hull_Random) {
	unsigned seed = time(NULL);
	cout << "Seed " << seed << endl;
	srand(seed); rand(); rand();
	int ts = 50;
	while (ts--) {
		vector<vec> p(10000);
		for (unsigned i = 0; i < p.size(); i++) {
			p[i].x = rand()%2000001;
			p[i].y = rand()%2000001;
			p[i].x -= 1000000;
			p[i].y -= 1000000;
		}
		EXPECT_TRUE(testConvex(p, {}, 0)) << " simple";
		EXPECT_TRUE(testConvex(p, {}, 0)) << " in_border";
	}
}

TEST(geometry, polygon_inter) {
	vector<vec> v({vec(3,4), vec(5, 2), vec(7, 3)});
	cir c(vec(3,4), 5);
	EXPECT_EQ(polygon_inter(&v[0],v.size(),c), c.triang_inter(v[1],v[2])) << "Same center inside";

	v[1] = vec(30,4); v[2] = vec(3,84);
	EXPECT_EQ(polygon_inter(&v[0],v.size(),c), c.arc_area(v[1],v[2])) << "Same center outside";

	c.c = vec(4,5);
	v.resize(2);
	EXPECT_NEAR(polygon_inter(&v[0],v.size(),c), 0., 1e-12) << "Degenerate";
}

TEST(geometry, polygon_pos) {
	// Geogebra: https://ggbm.at/BaFwEPXZ
	vector<vec> p({ vec(14,14), vec(20,8), vec(10,2), vec(2,12), vec(6,16), vec(10,16), vec(10,20), vec(6,22), vec(14,24), vec(14,26), vec(6,26), vec(19,31), vec(10,31), vec(6,33), vec(19,35), vec(10,35), vec(10,39), vec(5,39), vec(17,42), vec(10,45), vec(10,48), vec(13,50), vec(24,44) });

	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,10)), 1); // B_0
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,18)), 0); // B_1
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,22)), 1); // B_2
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,25)), -1); // B_3
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,27)), 1); // B_4
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,29)), -1); // B_5
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,32)), 1); // B_6
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,34)), -1); // B_7
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,36)), 0); // B_8
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,40)), 1); // B_9
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(13,41)), 0); // B_{10}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(14,14)), 0); // B_{11}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,20)), 0); // B_{12}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(19,33)), 1); // B_{13}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(5,13)), 1); // B_{14}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(5,18)), -1); // B_{15}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(6,12)), 1); // B_{16}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,-1)), -1); // B_{17}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(20,6)), -1); // B_{18}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(20,10)), -1); // B_{19}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,42)), -1); // B_{20}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(10,47)), 0); // B_{21}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(13,47)), 1); // B_{22}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(16,9)), 1); // B_{23}
	EXPECT_EQ(polygon_pos(&p[0], p.size(), vec(17,5)), -1); // B_{24}
}

/*
TEST(geometry, polygon_pos_convex) {
	vector<vec> p({ {5,10},{6,8},{9,6},{11,8},{11,10},{10,12},{9,13},{6,12} });
	ASSERT_EQ(polygon_pos_convex(&p[0], p.size(), {7,6}), -1);

	// inside
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {6,10}), 1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {8,12}), 1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {7,8}), 1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {10,8}), 1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {8,9}), 1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {6,9}), 1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {8,7}), 1);

	// border
	for (vec a : p)
		EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), a), 0) << "where a = " << a << endl;
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {11,9}), 0);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {10,7}), 0);

	// outside
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {12,8}), -1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {5,8}), -1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {5,7}), -1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {7,14}), -1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {15,14}), -1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {12,10}), -1);
	EXPECT_EQ(polygon_pos_convex(&p[0], p.size(), {12,11}), -1);

	int n = p.size();
	p.pb(p[0]);
	p.pb(p[1]);
	p.pb(p[2]);
	p.pb(p[3]);
	for (int k = 2; k <= 3; k++) { 
		EXPECT_EQ(polygon_pos_convex(&p[k], n, {8,5}), -1) << p[k] << " (k = " << k << ")";
		EXPECT_EQ(polygon_pos_convex(&p[k], n, {10,7}), 0) << p[k] << " (k = " << k << ")";
		EXPECT_EQ(polygon_pos_convex(&p[k], n, {11,8}), 0, 1) << p[k] << " (k = " << k << ")";
		EXPECT_EQ(polygon_pos_convex(&p[k], n, {12,9}), -1) << p[k] << " (k = " << k << ")";
	}
}
*/

pii pair_rev (pii p) { return pii(p.second,p.first); }

TEST(geometry, antipodal) {
	// geogebra: https://ggbm.at/uaEAPcZa

	vector<vec> A({vec(1,1), vec(2,-2), vec(8,-1), vec(6,4), vec(2,4)}); // in geogebra, points in poly A
	vector<vec> to_a({vec(-1,-2),vec(3,0), vec(1,3)}); // in geogebra, A[0] - a_i for each i
	EXPECT_EQ(antipodal(&A[0], A.size(), to_a[0]), pii(1,3)) << "a_0 simple";
	EXPECT_EQ(antipodal(&A[0], A.size(), to_a[1]), pii(2,0)) << "a_1 all in one side";
	EXPECT_EQ(antipodal(&A[0], A.size(), to_a[2]), pii(3,1)) << "a_2 ties";
	for (unsigned int i = 0; i < to_a.size(); i++) {
		EXPECT_EQ(antipodal(&A[0], A.size(), to_a[i]), pair_rev(antipodal(&A[0], A.size(), vec(0,0) - to_a[i]))) << "opposite dir";
	}
}
