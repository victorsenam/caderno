typedef double cood;
const double eps = 1e-8;

#include "gtest/gtest.h"
#include "../code/geometry.cpp"

bool operator== (vec a, vec b)
{ return (abs(a.x - b.x) < eps && abs(a.y - b.y) < eps); }

TEST(geometry_vec_dbl, Rotate) {
	EXPECT_EQ(vec(1,0).rotate(0), vec(1,0));
	EXPECT_EQ(vec(1,0).rotate(.5*pi), vec(0,1));
	EXPECT_EQ(vec(1,0).rotate(pi), vec(-1,0));
	EXPECT_EQ(vec(1,0).rotate(1.5*pi), vec(0,-1));
	EXPECT_EQ(vec(1,0).rotate(2*pi), vec(1,0));

	EXPECT_EQ(vec(1,0).rotate(.25*pi), vec(sqrt(.5), sqrt(.5)));
	EXPECT_EQ(vec(416.942431806166155,466.834976408843204).rotate(1.728496650520573), vec(-526.521805830923995, 338.453356644054281));
}

TEST(geometry_vec_dbl_STRESS, SidePrecision) {
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

		ASSERT_EQ(ref.sd(main,to_left), -1) << to_left << " should be to the left of " << ref << " " << main << endl;
		ASSERT_EQ(ref.sd(to_left,main), 1) << main << " should be to the right of " << ref << " " << to_left << endl;
		ASSERT_EQ(ref.sd(main,colin), 0) << colin << " shoulde be collinear to " << ref << " " << main << endl;
	}
}

TEST(geometry_vec_dbl_STRESS, ComparePrecision) {
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

TEST(geometry_vec_dbl_STRESS, CompareSort) {
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

		vec anc = (vec(1.,0.).rotate(rnd_angle(gen)))*rnd_module(gen);

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
			cartesian[i] = anc + (vec(1,0).rotate(polar[i].first))*polar[i].second;
		}

		// sort and check
		sort(polar.begin(), polar.end());
		sort(cartesian.begin(), cartesian.end(), [anc] (vec a, vec b) {
			return vec(anc).compare(a,b);
		});

		for (int i = 0; i < m; i++) {
			vec cur = anc + (vec(1,0).rotate(polar[i].first)*polar[i].second);
			ASSERT_EQ(cartesian[i], cur) << "Test " << tt << " item " << i + 1 << ": " << setprecision(30) << cartesian[i] << " " << cur;
		}
	}
}
