typedef long long cood;
const cood eps = 0;

#include "gtest/gtest.h"
#include "../code/geometry.cpp"

bool operator== (vec a, vec b)
{ return a.x == b.x && a.y == b.y; }

TEST(geometry_vec, Operations) {
	vec a(45,16), b(50,13);
	ll c = 10;

	EXPECT_EQ(a.x, 45);
	EXPECT_EQ(a.y, 16);

	EXPECT_EQ(a-b, vec(-5, 3));
	EXPECT_EQ(a+b, vec(95, 29));
	EXPECT_EQ(a*c, vec(450, 160));
	EXPECT_EQ(a/c, vec(4, 1));

	EXPECT_EQ(a^b, -215);
	EXPECT_EQ(a*b, 2458);

	EXPECT_EQ(a.sq(), 2281);
	EXPECT_DOUBLE_EQ(a.nr(), sqrt(a.sq()));
}

TEST(geometry_vec, CrossProduct) {
	EXPECT_EQ(vec(0,2).ccw(vec(1,0),vec(3,2)), 1) << "should return 1 when left";	// left
	EXPECT_EQ(vec(2,0).ccw(vec(1,0),vec(3,2)), -1); // right
	EXPECT_EQ(vec(2,1).ccw(vec(1,0),vec(3,2)), 0); // colin
	EXPECT_EQ(vec(2,1).ccw(vec(3,2),vec(1,0)), 0); // colin
	EXPECT_EQ(vec(1,0).ccw(vec(2,1),vec(3,2)), 0); // before line
	EXPECT_EQ(vec(1,0).ccw(vec(3,2),vec(2,1)), 0); // after line
	EXPECT_EQ(vec(-50,-48).ccw(vec(-49,-50),vec(-47,-48)), 1); // all neg
	EXPECT_EQ(vec(-3, 1).ccw(vec(1,-5),vec(-4,10)), 1); // mixed

	EXPECT_EQ(vec(11,-11).ccw(vec(0,0),vec(-1,0)), 1); // extra test

	EXPECT_EQ(vec(99,101).cross(vec(100,100),vec(101,101)), 2);
	EXPECT_EQ(vec(10,13).cross(vec(80,83),vec(-20,-17)), 0);
}

TEST(geometry_vec, dir) {
	EXPECT_EQ(vec(5,5).dir(vec(4,5), vec(6,5)), -1);
	EXPECT_EQ(vec(5,5).dir(vec(6,6), vec(7,7)), 1);
	EXPECT_EQ(vec(5,5).dir(vec(4,4), vec(3,3)), 1);
	EXPECT_EQ(vec(7,6).dir(vec(8,6), vec(5,6)), -1);
	EXPECT_EQ(vec(5,4).dir(vec(6,4), vec(5,5)), 0);
}

TEST(geometry_vec, halfplane) {
	EXPECT_FALSE(vec(1,1).halfplane());
	EXPECT_FALSE(vec(1,0).halfplane());
	EXPECT_FALSE(vec(0,0).halfplane());
	EXPECT_FALSE(vec(0,1).halfplane());
	EXPECT_FALSE(vec(-1,1).halfplane());
	EXPECT_FALSE(vec(-1000,1).halfplane());
	EXPECT_FALSE(vec(-1,100).halfplane());

	EXPECT_TRUE(vec(-1,0).halfplane());
	EXPECT_TRUE(vec(-1000,0).halfplane());
	EXPECT_TRUE(vec(1,-1).halfplane());
	EXPECT_TRUE(vec(10000,-1).halfplane());
	EXPECT_TRUE(vec(-10,-1).halfplane());
	EXPECT_TRUE(vec(0,-1).halfplane());
	EXPECT_TRUE(vec(0,-100).halfplane());
}

TEST(geometry_vec, compare) {
	EXPECT_FALSE(vec(0,0).compare(vec(-1,0),vec(1,0))) << "Works ok from origin.";
	EXPECT_FALSE(vec(0,0).compare(vec(11,-11),vec(-1,0))) << "Works ok for lower half.";
	EXPECT_TRUE(vec(0,0).compare(vec(1,0),vec(0,1))) << "Compares first by halfplane.";
	EXPECT_TRUE(vec(0,0).compare(vec(1,0),vec(2,0))) << "Unties with distance.";
	EXPECT_TRUE(vec(2,1).compare(vec(1,1),vec(1,0))) << "Works ok from some other point.";

	vector<vec> ans({
		vec(3,0), vec(10,0),
		vec(3,1),
		vec(4,4), vec(748, 748),
		vec(0,5),
		vec(-1,0), vec(-2,0),
		vec(-1,-4),
		vec(401, -4)
	});

	vector<vec> res = ans;
	srand(42); rand(); rand();
	random_shuffle(res.begin(), res.end());
	sort(res.begin(), res.end(), [] (vec a, vec b) { return vec(0,0).compare(a,b); });

	EXPECT_EQ(res, ans) << "Sorts a vector correctly";
}

TEST(geometry_vec, in_seg) {
	EXPECT_TRUE(vec(1, 1).in_seg(vec(0, 0), vec(2, 2)));
	EXPECT_TRUE(vec(1, 1).in_seg(vec(0, 0), vec(1, 1))) << "Tip not included";
	EXPECT_TRUE(vec(1, 1).in_seg(vec(1, 1), vec(1, 1))) << "Degenerate segment not working";
	EXPECT_FALSE(vec(0, 0).in_seg(vec(1, 1), vec(1, 1))) << "Degenerate segment not working";

	EXPECT_FALSE(vec(0, 1).in_seg(vec(-1e8, -1e8), vec(1.2e8, 1.2e8)));
	EXPECT_TRUE(vec(0, 0).in_seg(vec(-1e8, -1e8), vec(1.2e8, 1.2e8)));
	EXPECT_FALSE(vec(0, 0).in_seg(vec(-1e8, -1e8), vec(1.2e8, int(1.2e8) + 1)));
}

TEST(geometry_vec, in_seg_Generated) {
	// Very close to the segments.
	EXPECT_FALSE(vec(4, 3).in_seg(vec(100000006, 100000003), vec(-99999996, -99999995)));
	EXPECT_FALSE(vec(-1, 4).in_seg(vec(-100000000, -99999998), vec(100000000, 100000008)));
	EXPECT_FALSE(vec(-10000, -9997).in_seg(vec(100000004, 100000003), vec(-99999999, -99999993)));
	EXPECT_FALSE(vec(3, 4).in_seg(vec(-99999993, -99999999), vec(100000001, 100000009)));
	EXPECT_FALSE(vec(-10000, -9999).in_seg(vec(-99999994, -99999997), vec(100000003, 100000009)));
	EXPECT_FALSE(vec(4, 4).in_seg(vec(-99999999, -99999998), vec(100000008, 100000007)));
	EXPECT_FALSE(vec(-10000, -9997).in_seg(vec(100000009, 100000005), vec(-100000000, -99999991)));
	EXPECT_FALSE(vec(-10000, -9998).in_seg(vec(100000006, 100000006), vec(-99999994, -99999991)));
	EXPECT_FALSE(vec(1, 5).in_seg(vec(-100000000, -99999991), vec(100000004, 100000003)));
	EXPECT_FALSE(vec(-10000, -9999).in_seg(vec(100000007, 100000009), vec(-99999996, -99999994)));
	EXPECT_FALSE(vec(0, 7).in_seg(vec(-99999998, -99999993), vec(100000000, 100000009)));
	EXPECT_FALSE(vec(-10000, -9997).in_seg(vec(-99999997, -99999995), vec(100000004, 100000009)));
	EXPECT_FALSE(vec(-10000, -9999).in_seg(vec(100000002, 100000001), vec(-99999999, -99999997)));
	EXPECT_FALSE(vec(-10000, -9996).in_seg(vec(-100000000, -99999995), vec(100000002, 100000007)));
	EXPECT_FALSE(vec(4, 5).in_seg(vec(-99999997, -99999995), vec(100000007, 100000007)));
	EXPECT_FALSE(vec(-10000, -9995).in_seg(vec(100000005, 100000009), vec(-100000000, -99999995)));
	EXPECT_FALSE(vec(-10000, -9989).in_seg(vec(100000051, 100000126), vec(-99999832, -99999884)));
	EXPECT_FALSE(vec(67, 55).in_seg(vec(100000036, 100000056), vec(-99999901, -99999945)));
	EXPECT_FALSE(vec(-9994, -10000).in_seg(vec(-99999899, -99999887), vec(100000071, 100000046)));
	EXPECT_FALSE(vec(-9978, -10000).in_seg(vec(-99999956, -99999970), vec(100000188, 100000157)));
	EXPECT_FALSE(vec(-10000, -9930).in_seg(vec(100000097, 100000197), vec(-99999870, -99999829)));
	EXPECT_FALSE(vec(91, 129).in_seg(vec(100000054, 100000147), vec(-99999870, -99999887)));
	EXPECT_FALSE(vec(100, 91).in_seg(vec(100000084, 100000064), vec(-99999858, -99999856)));
	EXPECT_FALSE(vec(-100, -103).in_seg(vec(-99999830, -99999925), vec(100000067, 100000157)));
	EXPECT_FALSE(vec(100, -596).in_seg(vec(-99989262, -99996145), vec(100005911, 100011403)));
	EXPECT_FALSE(vec(100, 4539).in_seg(vec(100004997, 100018538), vec(-99992307, -99996969)));
	EXPECT_FALSE(vec(100, 11057).in_seg(vec(-99869074, -99871063), vec(100156664, 100180604)));
	EXPECT_FALSE(vec(-100, 25215).in_seg(vec(-99920531, -99825748), vec(100056815, 100012567)));

	// On the middle
	EXPECT_TRUE(vec(38846282, 38846281).in_seg(vec(-99999988, -99999989), vec(100000012, 100000011)));
	EXPECT_TRUE(vec(33333341, 33333351).in_seg(vec(-99999989, -99999985), vec(100000006, 100000019)));
	EXPECT_TRUE(vec(27, 25).in_seg(vec(-99999974, -99999979), vec(100000028, 100000029)));
	EXPECT_TRUE(vec(11111132, 11111126).in_seg(vec(-99999978, -99999989), vec(100000020, 100000018)));
	EXPECT_TRUE(vec(2529668, 7832063).in_seg(vec(-98556218, -93784612), vec(103615554, 109448738)));
	EXPECT_TRUE(vec(-42927874, -49279064).in_seg(vec(-93517596, -99295593), vec(108841292, 100770523)));
	EXPECT_TRUE(vec(5478471, 6433667).in_seg(vec(-94943320, -96064829), vec(105900262, 108932163)));
	EXPECT_TRUE(vec(5112649, 5713558).in_seg(vec(-99648916, -95077828), vec(109874214, 106504944)));
	EXPECT_TRUE(vec(114784348, 78778014).in_seg(vec(-73117562, -66246801), vec(164891524, 117451298)));
	EXPECT_TRUE(vec(79565493, 141936603).in_seg(vec(-35489555, -234209), vec(108329255, 177479306)));
	EXPECT_TRUE(vec(17272162, 45923000).in_seg(vec(-40061355, -1556791), vec(189272713, 188362373)));
	EXPECT_TRUE(vec(33546011, 85982218).in_seg(vec(-78379494, -77529392), vec(100701314, 184089184)));
	EXPECT_TRUE(vec(71505148, 59430354).in_seg(vec(-13132301, -58339227), vec(127930114, 137943408)));
}

::testing::AssertionResult in_conv_poly (vec v[], int n, vector<int> & p, vec x, int a) {
	int prec, succ;
	if (x.in_conv_poly(v, n, p, prec, succ)) {
		if (prec != a)
			return ::testing::AssertionFailure() << x << " is after " << prec << " instead of " << a;
		return ::testing::AssertionSuccess();
	} else {
		return ::testing::AssertionFailure() << x << " is outside covering ]" << prec << ".." << succ << "[";
	}
}

::testing::AssertionResult in_conv_poly (vec v[], int n, vector<int> & p, vec x, int a, int b) {
	int prec, succ;
	if (!x.in_conv_poly(v, n, p, prec, succ)) {
		if (prec != a || succ != b)
			return ::testing::AssertionFailure() << x << " covers ]" << prec << ".." << succ << "[ instead of ]" << a << ".." << b << "[";
		return ::testing::AssertionSuccess();
	} else {
		return ::testing::AssertionFailure() << x << " is inside after " << prec;
	}
}

TEST(geometry_vec, in_conv_poly) {
	vec v[] = { vec(0,0), vec(1,-2), vec(2,-3), vec(3,-3), vec(3,0), vec(2,1), vec(1,1) };
	int n = 7;

	vector<int> p(n);
	for (int i = 0; i < n; i++)
		p[i] = i;

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(4,-2), 3, 4)) << "Outside point with no remotions";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(6,-2), 3, 5)) << "Point removing forwards";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(4,-4), 2, 4)) << "Point removing backwards";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(4,0), 3, 5)) << "Point removing over";

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(4,-1), 3, 5)) << "Removing a border point";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(3,1), 3, 6)) << "Removing two border points";

	for (int i = 0; i < n; i++)
		EXPECT_TRUE(in_conv_poly(v, n, p, v[i], i)) << "Polygon vertexes should not be removed";
	
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(1,0), 4)) << "Point inside polygon";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(2,-1), 3)) << "Point inside polygon";

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(0,-1), 0, 2)) << "Point to the right of polygon";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(1,-3), 0, 3)) << "Point to the right of polygon";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(1,3), 4, 0)) << "Point to the left of polygon";

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(-1,0), 6, 2)) << "Point covers v[0]";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(-3,-1), 6, 2)) << "Point covers v[0]";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(-1,-1), 6, 2)) << "Point covers v[0] and some from the ending";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(-3,-3), 6, 3)) << "Point covers v[0] collinearly and some from the beginning collinearly";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(-1,2), 5, 1)) << "Point covers v[0] collinearly and some from the ending";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(-3,6), 4, 1)) << "Point covers v[0] collinearly and many from the ending";

	// collinear to v[1]
	// collinear to v[n-1]
}

TEST(geometry_vec, in_conv_poly__Triangle) {
	vec v[6];
	v[0] = vec(2,2); v[1] = vec(4,2); v[2] = vec(2,4);
	int n = 3;

	vector<int> p(n);
	for (int i = 0; i < n; i++) {
		v[i+n] = v[i];
		p[i] = i;
	}
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(2,2), 0)) << "Over polygon vertex";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(4,2), 1)) << "Over polygon vertex";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(2,4), 2)) << "Over polygon vertex";

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(4,4), 1, 2)) << "No remotions";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(4,0), 0, 1)) << "No remotions";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(0,4), 2, 0)) << "No remotions";

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(8,0), 0, 2)) << "Removing";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(0,8), 1, 0)) << "Removing";

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(0,0), 2, 1)) << "Removing v[0]";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(0,2), 2, 1)) << "Removing v[0]";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(0,1), 2, 1)) << "Removing v[0]";

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(2,0), 2, 1)) << "Collinear to removed point v[0]";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(0,2), 2, 1)) << "Collinear to removed point v[0]";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(6,0), 0, 2)) << "Collinear to removed point v[1]";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(6,2), 0, 2)) << "Collinear to removed point v[1]";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(0,6), 1, 0)) << "Collinear to removed point v[2]";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(2,6), 1, 0)) << "Collinear to removed point v[2]";

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(3,2), 1)) << "In polygon segment";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(3,3), 1)) << "In polygon segment";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(2,3), 2)) << "In polygon segment";

	EXPECT_TRUE(in_conv_poly(v+1, n, p, vec(4,4), 0, 1)) << "Shifted beginning";
	EXPECT_TRUE(in_conv_poly(v+1, n, p, vec(6,0), 2, 1)) << "Shifted beginning";
	EXPECT_TRUE(in_conv_poly(v+1, n, p, vec(6,2), 2, 1)) << "Shifted beginning";

	EXPECT_TRUE(in_conv_poly(v+2, n, p, vec(4,4), 2, 0)) << "Shifted beginning";
	EXPECT_TRUE(in_conv_poly(v+2, n, p, vec(6,0), 1, 0)) << "Shifted beginning";
	EXPECT_TRUE(in_conv_poly(v+2, n, p, vec(6,2), 1, 0)) << "Shifted beginning";
}

TEST(geometry_vec, in_conv_poly__Segment) {
	vec v[2] = { vec(-10,-10), vec(10,10) };
	int n = 2;

	vector<int> p(n);
	for (int i = 0; i < n; i++)
		p[i] = i;

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(0,0), 1)) << "Inside segment";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(20,20), 0, 0)) << "Should work when point covers last tip";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(-20,-20), 1, 1)) << "Should work when point covers first tip";

	EXPECT_TRUE(in_conv_poly(v, n, p, vec(-10,10), 1, 0)) << "Should work when point forms a triangle";
	EXPECT_TRUE(in_conv_poly(v, n, p, vec(10,-10), 0, 1)) << "Should work when point forms a triangle";
}

TEST(geometry_vec, dist2_seg) {
	EXPECT_DOUBLE_EQ(vec(1,1).dist2_seg(vec(4,0), vec(-3,-1)), 2.);
}
