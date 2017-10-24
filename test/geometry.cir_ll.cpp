// Geogebra drawings for these tests : https://ggbm.at/sjWhFMQm

typedef long long cood;
const double eps = 0;

#include "gtest/gtest.h"
#include "../code/geometry.cpp"

bool operator== (vec a, vec b)
{ return (abs(a.x - b.x) < eps && abs(a.y - b.y) < eps); }

::std::ostream& operator<<(::std::ostream& os, const cir& c)
{ return os << "(" << c.c << "," << c.r << ")"; }

const vector<cir> circles({ 
	cir({ vec(-250,50), 100 }),
	cir({ vec(-50,0), 340 }),
	cir({ vec(-50,-250), 270 }),
	cir({ vec(200,100), 200 }),
	cir({ vec(-1200, 100), 5 }),
	cir({ vec(-1191, 112), 10 }),
	cir({ vec(-800,-500), 100}),
	cir({ vec(-800,-400), 200 })
});

const vector<vec> points({
	vec(-250,50),
	vec(-50,0),
	vec(-50,-250),
	vec(200,100),
	vec(-390,0),
	vec(-100,-100),
	vec(0,200),
	vec(400,0),
	vec(400,100),
	vec(-320,-255),
	vec(100,-50),
	vec(-180,-20),
	vec(-1200, 100),
	vec(-1197,104),
	vec(-1191,112)
});

const vector<pair<vec,vec> > lines({
	pair<vec,vec>(vec(-1205,110),vec(-1185,95)),
	pair<vec,vec>(vec(-400,300),vec(300,-400)),
	pair<vec,vec>(vec(300,400),vec(300,-300)),
	pair<vec,vec>(vec(-400,100),vec(-500,200)),
	pair<vec,vec>(vec(-200,400), vec(0,-200))
});

TEST(geometry_cir, contains) {
	bool res[][points.size()] = {
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{1,1,1,1,1,1,1,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,1,0,0,0,0,1,1,0,0,0},
		{0,0,0,1,0,0,0,0,1,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	for (unsigned int i = 0; i < circles.size(); i++) {
		for (unsigned int j = 0; j < points.size(); j++) {
			if (res[i][j])
				EXPECT_TRUE(cir(circles[i]).contains(points[j])) << circles[i] << " should contain " << points[j] << ".";
			else
				EXPECT_FALSE(cir(circles[i]).contains(points[j])) << circles[i] << " should not contain " << points[j] << ".";
		}
	}
}

TEST(geometry_cir, has_inter) {
	bool res[][circles.size()] = {
		{1,1,1,0,0,0,0,0},
		{1,1,1,1,0,0,0,0},
		{1,1,1,1,0,0,0,0},
		{0,1,1,1,0,0,0,0},
		{0,0,0,0,1,1,0,0},
		{0,0,0,0,1,1,0,0},
		{0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,1,1}
	};

	for (unsigned int i = 0; i < circles.size(); i++) {
		for (unsigned int j = 0; j < circles.size(); j++) {
			if (res[i][j])
				EXPECT_TRUE(cir(circles[i]).has_inter(circles[j])) << circles[i] << " should intersect " << circles[j] << ".";
			else
				EXPECT_FALSE(cir(circles[i]).has_inter(circles[j])) << circles[i] << " should not intersect " << circles[j] << ".";
		}
	}
}

TEST(geometry_cir, has_inter_lin) {
	bool res[][lines.size()] = {
		{0,1,0,1,0},
		{0,1,0,1,1},
		{0,1,0,1,1},
		{0,0,1,0,0},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{0,0,0,0,0},
		{1,0,0,0,0}
	};

	for (unsigned int i = 0; i < circles.size(); i++) {
		for (unsigned int j = 0; j < lines.size(); j++) {
			if (res[i][j])
				EXPECT_TRUE(cir(circles[i]).has_inter_lin(lines[j].first,lines[j].second)) << circles[i] << " should intersect line (" << lines[j].first << "," << lines[j].second << ").";
			else
				EXPECT_FALSE(cir(circles[i]).has_inter_lin(lines[j].first,lines[j].second)) << circles[i] << " should not intersect line (" << lines[j].first << "," << lines[j].second << ").";
		}
	}
}

TEST(geometry_cir, has_inter_seg) {
	bool res[][lines.size()] = {
		{0,1,0,0,0},
		{0,1,0,0,1},
		{0,1,0,0,1},
		{0,0,1,0,0},
		{1,0,0,0,0},
		{1,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0}
	};

	for (unsigned int i = 0; i < circles.size(); i++) {
		for (unsigned int j = 0; j < lines.size(); j++) {
			if (res[i][j])
				EXPECT_TRUE(cir(circles[i]).has_inter_seg(lines[j].first,lines[j].second)) << circles[i] << " should intersect segment (" << lines[j].first << "," << lines[j].second << ").";
			else
				EXPECT_FALSE(cir(circles[i]).has_inter_seg(lines[j].first,lines[j].second)) << circles[i] << " should not intersect segment (" << lines[j].first << "," << lines[j].second << ").";
		}
	}
}

TEST(geometry_cir, contains_cir) {
	bool res[][circles.size()] = {
		{0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}
	};

	for (unsigned int i = 0; i < circles.size(); i++) {
		for (unsigned int j = 0; j < lines.size(); j++) {
			if (res[i][j])
				EXPECT_TRUE(cir(circles[i]).contains(circles[j])) << circles[i] << " should contain " << circles[j] << ".";
			else
				EXPECT_FALSE(cir(circles[i]).contains(circles[j])) << circles[i] << " should not contain " << circles[j] << ".";
		}
	}
}
