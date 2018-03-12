#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood;
const double eps = 1e-8;

#include "gtest/gtest.h"
#include "../../code/geometry/basic.cpp"

bool operator== (cir a, cir b)
{ return (a.c == b.c && abs(a.r - b.r) <= eps); }

// vec
TEST(geometry_basic_vec, rotate) {
	EXPECT_EQ(vec(1,0).rotate(0), vec(1,0));
	EXPECT_EQ(vec(1,0).rotate(.5*pi), vec(0,1));
	EXPECT_EQ(vec(1,0).rotate(pi), vec(-1,0));
	EXPECT_EQ(vec(1,0).rotate(1.5*pi), vec(0,-1));
	EXPECT_EQ(vec(1,0).rotate(2*pi), vec(1,0));

	EXPECT_EQ(vec(1,0).rotate(.25*pi), vec(sqrt(.5), sqrt(.5)));
	EXPECT_EQ(vec(416.942431806166155,466.834976408843204).rotate(1.728496650520573), vec(-526.521805830923995, 338.453356644054281));
}

TEST(geometry_basic_vec, proj) {
	EXPECT_EQ(vec(-2.7,1.8).proj(vec(-5.4, 0.6), vec(-1.5, -0.7)), vec(-3.33, -0.09));
	EXPECT_EQ(vec(-5.3,2.9).proj(vec(-5.4, 0.6), vec(-1.5, -0.7)), vec(-6, 0.8));
	EXPECT_EQ(vec(-4.5,-3).proj(vec(-5.4, 0.6), vec(-1.5, -0.7)), vec(-3.51,-0.03));
	EXPECT_EQ(vec(-4.5,-3).proj(vec(2.5,1), vec(1.5, 4)), vec(3,-0.5));
	EXPECT_EQ(vec(0,2).proj(vec(2.5,1), vec(1.5, 4)), vec(1.95,2.65));
}

TEST(geometry_basic_vec, angle) {
	EXPECT_DOUBLE_EQ(vec(0,0).angle(vec(2,0),vec(1,0)), 0.);
	EXPECT_DOUBLE_EQ(vec(0,0).angle(vec(2,0),vec(0,1)), .5*pi);
	EXPECT_DOUBLE_EQ(vec(0,0).angle(vec(2,0),vec(0,-1)), -.5*pi);

	EXPECT_GT(vec(3,2).angle(vec(5,5),vec(4,5)),0.);
	EXPECT_GT(vec(3,2).angle(vec(5,5),vec(2,2)),0.);
	EXPECT_LT(vec(3,2).angle(vec(5,5),vec(3,1)),0.);
	EXPECT_LT(vec(3,2).angle(vec(5,5),vec(5,2)),0.);

	EXPECT_DOUBLE_EQ(abs(vec(3,2).angle(vec(4,2),vec(2,2))), pi);
}

TEST(geometry_basic_vec, nr) {
	EXPECT_DOUBLE_EQ(vec(1,0).nr(vec(0,1)), sqrt(2));
	EXPECT_DOUBLE_EQ(vec(3,3).nr(vec(7,0)), 5);
	EXPECT_DOUBLE_EQ(vec(1,0).nr(vec(1,0)), 0);
}

TEST(geometry_basic_vec, dist2_lin) {
	EXPECT_DOUBLE_EQ(vec(0,1).dist2_lin(vec(1,0), vec(3,0)), 1);
	EXPECT_DOUBLE_EQ(vec(1,1).dist2_lin(vec(1,0), vec(3,0)), 1);
	EXPECT_DOUBLE_EQ(vec(2,1).dist2_lin(vec(1,0), vec(3,0)), 1);
	EXPECT_DOUBLE_EQ(vec(3,1).dist2_lin(vec(1,0), vec(3,0)), 1);
	EXPECT_DOUBLE_EQ(vec(4,1).dist2_lin(vec(1,0), vec(3,0)), 1);

	EXPECT_DOUBLE_EQ(vec(0,11).dist2_lin(vec(2,1), vec(1,4)), 1.6);
	EXPECT_DOUBLE_EQ(vec(0,2).dist2_lin(vec(2,1), vec(1,4)), 2.5);
	EXPECT_DOUBLE_EQ(vec(1,1).dist2_lin(vec(4,0), vec(-3,-1)), 2.);
	EXPECT_DOUBLE_EQ(vec(0,0).dist2_lin(vec(-8,8), vec(-7,5)), 25.6);

 	// Geogebra: https://ggbm.at/nMx6fY5u
	vec a(5,2);
	EXPECT_DOUBLE_EQ(a.dist2_lin(vec(15,0), vec(0,3)), 0) << "from A to BC";
	EXPECT_DOUBLE_EQ(a.dist2_lin(vec(5,1), vec(5,-3)), 0) << "from A to DE";
	EXPECT_DOUBLE_EQ(a.dist2_lin(vec(6,4), vec(3,6)), 4.9230769230769234) << "from A to FG";
	EXPECT_DOUBLE_EQ(a.dist2_lin(vec(3,6), vec(6,4)), 4.9230769230769234) << "from A to GF";
	EXPECT_DOUBLE_EQ(a.dist2_lin(vec(5,3), vec(9,4)), 0.94117647058823528) << "from A to HI";
	EXPECT_DOUBLE_EQ(a.dist2_lin(vec(7,-1), vec(5,2)), 0) << "from A to JA";
	EXPECT_DOUBLE_EQ(a.dist2_lin(vec(4,0), vec(4,0)), a.sq(vec(4,0))) << "Degenerate";
}

TEST(geometry_basic_vec, dist2_seg) {
	EXPECT_DOUBLE_EQ(vec(0,1).dist2_seg(vec(1,0), vec(3,0)), 2);
	EXPECT_DOUBLE_EQ(vec(1,1).dist2_seg(vec(1,0), vec(3,0)), 1);
	EXPECT_DOUBLE_EQ(vec(2,1).dist2_seg(vec(1,0), vec(3,0)), 1);
	EXPECT_DOUBLE_EQ(vec(3,1).dist2_seg(vec(1,0), vec(3,0)), 1);
	EXPECT_DOUBLE_EQ(vec(4,1).dist2_seg(vec(1,0), vec(3,0)), 2);

	EXPECT_DOUBLE_EQ(vec(0,11).dist2_seg(vec(2,1), vec(1,4)), 50);
	EXPECT_DOUBLE_EQ(vec(0,2).dist2_seg(vec(2,1), vec(1,4)), 2.5);
	EXPECT_DOUBLE_EQ(vec(1,1).dist2_seg(vec(4,0), vec(-3,-1)), 2.);
	EXPECT_DOUBLE_EQ(vec(0,0).dist2_seg(vec(-8,8), vec(-7,5)), 74);

 	// Geogebra: https://ggbm.at/nMx6fY5u
	vec a(5,2);
	EXPECT_DOUBLE_EQ(a.dist2_seg(vec(15,0), vec(0,3)), 0) << "from A to BC";
	EXPECT_DOUBLE_EQ(a.dist2_seg(vec(5,1), vec(5,-3)), 1) << "from A to DE";
	EXPECT_DOUBLE_EQ(a.dist2_seg(vec(6,4), vec(3,6)), 5) << "from A to FG";
	EXPECT_DOUBLE_EQ(a.dist2_seg(vec(3,6), vec(6,4)), 5) << "from A to GF";
	EXPECT_DOUBLE_EQ(a.dist2_seg(vec(5,3), vec(9,4)), 1) << "from A to HI";
	EXPECT_DOUBLE_EQ(a.dist2_seg(vec(7,-1), vec(5,2)), 0) << "from A to JA";
	EXPECT_DOUBLE_EQ(a.dist2_lin(vec(4,0), vec(4,0)), a.sq(vec(4,0))) << "Degenerate";
}

TEST(geometry_basic_vec_rand, CrossProduct__Precision) {
	mt19937_64 gen(42);
	uniform_real_distribution<double> rnd_module(1e-9, 5e3);
	uniform_real_distribution<double> rnd_angle(0., 2.*pi);
	uniform_real_distribution<double> rnd_alpha(0.9,1.1);

	for (int tt = 1; tt <= 1000; tt++) {
		vec ref = (vec(1.,0.).rotate(rnd_angle(gen)))*rnd_module(gen);
		vec base = vec(1.,0.).rotate(rnd_angle(gen));

		vec main = ref + base*rnd_module(gen);
		vec colin = ref + base*rnd_module(gen);
		vec to_left = ref + base.rotate(rnd_angle(gen)*.5)*rnd_module(gen);

		ASSERT_EQ(ref.ccw(main,to_left), 1) << to_left << " should be to the left of " << ref << " " << main << endl;
		ASSERT_EQ(ref.ccw(to_left,main), -1) << main << " should be to the right of " << ref << " " << to_left << endl;
		ASSERT_EQ(ref.ccw(main,colin), 0) << colin << " shoulde be collinear to " << ref << " " << main << endl;
	}
}

TEST(geometry_basic_vec_rand, compare__Precision) {
	mt19937_64 gen(42);
	uniform_int_distribution<int> rnd_size(100, 10000);
	uniform_real_distribution<double> rnd_module(1e-9, 5e3);
	uniform_real_distribution<double> rnd_angle(0., 2.*pi);

	for (int tt = 1; tt <= 1000; tt++) {
		double o_ang = rnd_angle(gen), a_ang = rnd_angle(gen), b_ang = rnd_angle(gen);
		double o_mod = rnd_module(gen), a_mod = rnd_module(gen), b_mod = rnd_module(gen);
		b_ang = a_ang;
		vec o = vec(1,0).rotate(o_ang)*o_mod;
		vec a = o + vec(1,0).rotate(a_ang)*a_mod;
		vec b = o + vec(1,0).rotate(b_ang)*b_mod;

		bool polar = pair<double,double>(a_ang,a_mod) < pair<double,double>(b_ang,b_mod);
		bool cartesian = o.compare(a,b);

		ASSERT_EQ(polar, cartesian) << o << " " << a << " " << b;
	}
}

TEST(geometry_basic_vec_rand, compare__Sorting) {
	// generates a random anchor
	// generates random points
	// sorts them by the anchor two different ways
	// compares the results
	mt19937_64 gen(42);
	uniform_int_distribution<int> rnd_size(100, 10000);
	uniform_real_distribution<double> rnd_module(1e-9, 5e3);
	uniform_real_distribution<double> rnd_angle(0., 2.*pi);

	for (int tt = 1; tt <= 50; tt++) {
		int n = rnd_size(gen); int m = rnd_size(gen);
		if (n > m) swap(n, m);

		vec anc = (vec(0.,1.).rotate(rnd_angle(gen)))*rnd_module(gen);

		// generate n possible angles
		vector<double> angles(n);
		for (int i = 0; i < n; i++)
			angles[i] = rnd_angle(gen);

		// generate m vectors with two representantions
		uniform_int_distribution<int> rnd_angle_idx(0, n-1);
		vector<pair<double, double> > polar(m); // polar representation
		vector<vec> cartesian(m); // cartesian representation shifted by anc
		for (int i = 0; i < m; i++) {
			polar[i] = pair<double,double>(angles[rnd_angle_idx(gen)], rnd_module(gen));
			//polar[i] = pair<double,double>(rnd_angle(gen), rnd_module(gen));
			cartesian[i] = anc + (vec(0,1).rotate(polar[i].first))*polar[i].second;
		}

		// sort and check
		sort(polar.begin(), polar.end());
		sort(cartesian.begin(), cartesian.end(), [anc] (vec a, vec b) {
			return vec(anc).compare(a,b);
		});

		for (int i = 0; i < m; i++) {
			vec cur = anc + (vec(0,1).rotate(polar[i].first)*polar[i].second);
			ASSERT_EQ(cartesian[i], cur) << "Test " << tt << " item " << i + 1 << ": " << setprecision(30) << cartesian[i] << " " << cur;
		}
	}
}

// lin
void lin_sign_dist_test (vec p, vec s, vec t, string comm = "") {
	lin l(s,t);
	EXPECT_DOUBLE_EQ(sqrt(p.dist2_lin(s,t)), abs(lin(s,t).sign_dist(p))) << comm;
}
TEST(geometry_basic_lin, sign_dist) {
	lin_sign_dist_test(vec(0,1), vec(1,0), vec(3,0));
	lin_sign_dist_test(vec(1,1), vec(1,0), vec(3,0));
	lin_sign_dist_test(vec(2,1), vec(1,0), vec(3,0));
	lin_sign_dist_test(vec(3,1), vec(1,0), vec(3,0));
	lin_sign_dist_test(vec(4,1), vec(1,0), vec(3,0));

	lin_sign_dist_test(vec(0,11), vec(2,1), vec(1,4));
	lin_sign_dist_test(vec(0,2), vec(2,1), vec(1,4));
	lin_sign_dist_test(vec(1,1), vec(4,0), vec(-3,-1));
	lin_sign_dist_test(vec(0,0), vec(-8,8), vec(-7,5));

	EXPECT_DOUBLE_EQ(lin(vec(3,0),9).sign_dist(vec(13,8)), 10) << "vertical";
	EXPECT_DOUBLE_EQ(lin(vec(3,0),9).sign_dist(vec(-5,3)), -8) << "negative sign";
	EXPECT_DOUBLE_EQ(lin(vec(0,4),2).sign_dist(vec(0,1)), .5) << "horizontal";
	EXPECT_DOUBLE_EQ(lin(vec(0,4),3).sign_dist(vec(1,3)), 2.25) << "non-integer";
	EXPECT_DOUBLE_EQ(lin(vec(1,3),5).sign_dist(vec(1,2)), sqrt(10)/5) << "tilted";
	EXPECT_DOUBLE_EQ(lin(vec(1,3),5).sign_dist(vec(5,0)), 0) << "over"; 

 	// Geogebra: https://ggbm.at/nMx6fY5u
	vec a(5,2);
	lin_sign_dist_test(a, vec(15,0), vec(0,3), "from A to BC");
	lin_sign_dist_test(a, vec(5,1), vec(5,-3), "from A to DE");
	lin_sign_dist_test(a, vec(6,4), vec(3,6), "from A to FG");
	lin_sign_dist_test(a, vec(3,6), vec(6,4), "from A to GF");
	lin_sign_dist_test(a, vec(5,3), vec(9,4), "from A to HI");
	lin_sign_dist_test(a, vec(7,-1), vec(5,2), "from A to JA");
}

// none
TEST(geomtery_basic, dist2_seg) {
	// Geogebra: https://ggbm.at/JjWJj28v
	vec A[] = {vec(-8,7), vec(-2,6), vec(-6,3), vec(4,5), vec(10,4), vec(2,3), vec(-10,5), vec(-12,6), vec(-10,11), vec(-14,9)};
	
	EXPECT_EQ(dist2_seg(A[0],A[1],A[5],A[6]), A[1].dist2_seg(A[5],A[6])) << "in seg";
	EXPECT_EQ(dist2_seg(A[0],A[1],A[2],A[7]), A[0].dist2_seg(A[2],A[7])) << "in seg";
	EXPECT_EQ(dist2_seg(A[0],A[1],A[5],A[3]), A[1].sq(A[5])) << "to point";
	EXPECT_EQ(dist2_seg(A[0],A[1],A[3],A[4]), A[1].sq(A[3])) << "to point collinear";
	EXPECT_EQ(dist2_seg(A[0],A[1],A[3],A[8]), A[1].dist2_seg(A[3],A[8])) << "collinear tip";
	EXPECT_EQ(dist2_seg(A[0],A[1],A[6],A[8]), A[0].dist2_seg(A[6],A[8])) << "lines cross";

	EXPECT_EQ(dist2_seg(A[0],A[1],A[5],A[8]), 0) << "cross";
	EXPECT_EQ(dist2_seg(A[0],A[1],A[3],A[0]), 0) << "contained";

	EXPECT_EQ(dist2_seg(A[0],A[0],A[1],A[1]), A[0].sq(A[1])) << "degenerate 2 points";
	EXPECT_EQ(dist2_seg(A[6],A[6],A[0],A[1]), A[6].sq(A[0])) << "degenerate points to segment tip";
	EXPECT_EQ(dist2_seg(A[0],A[0],A[6],A[8]), A[0].dist2_seg(A[6],A[8])) << "degenerate points to segment middle";

	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 9; j++) {
			for (int k = 0; k <= 9; k++) 
				for (int l = 0; l <= 9; l++) {
					EXPECT_EQ(dist2_seg(A[i],A[j],A[k],A[l]), dist2_seg(A[i],A[j],A[l],A[k])) << "consistent when (i,j,k,l) = (" << i << "," << j << "," << k << "," << l << ") -> " << A[i] << A[j] << A[k] << A[l];
					EXPECT_EQ(dist2_seg(A[i],A[j],A[k],A[l]), dist2_seg(A[j],A[i],A[k],A[l])) << "consistent when (i,j,k,l) = (" << i << "," << j << "," << k << "," << l << ") -> " << A[i] << A[j] << A[k] << A[l];
					EXPECT_EQ(dist2_seg(A[i],A[j],A[k],A[l]), dist2_seg(A[k],A[l],A[i],A[j])) << "consistent when (i,j,k,l) = (" << i << "," << j << "," << k << "," << l << ") -> " << A[i] << A[j] << A[k] << A[l];
				}
		}
}

