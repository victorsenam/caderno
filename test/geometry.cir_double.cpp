// Geogebra drawings for these tests : https://ggbm.at/yt7gXv2Q

typedef double cood;
const double eps = 1e-8;

#include "gtest/gtest.h"
#include "../code/geometry.cpp"

bool operator== (vec a, vec b)
{ return (abs(a.x - b.x) < eps && abs(a.y - b.y) < eps); }
bool operator!= (vec a, vec b)
{ return !(a==b); }

::std::ostream& operator<<(::std::ostream& os, const cir& c)
{ return os << "(" << c.c << "," << c.r << ")"; }

vector<vec> points({
	vec(3.8,1.6),
	vec(2,1),
	vec(3.2,1.4),
	vec(2.6,1.2),
	vec(1.4,.8),
	vec(.8,.6),
	vec(1.7,.9),
	vec(1.85,0.95)
});

TEST(geometry_cir, inter_pts_cir) {
	cir c({ points[1], points[2].nr(points[1]) });

	for (unsigned int i = 2; i < points.size(); i++) {
		cir d({ points[0], points[i].nr(points[0]) });

		pair<vec,vec> p = c.inter_pts(d);
		for (vec v : {p.first, p.second}) {
			EXPECT_NEAR(v.nr(c.c), c.r, eps) << v << " should be on the border of " << c << ".";
			EXPECT_NEAR(v.nr(d.c), d.r, eps) << v << " should be on the border of " << d << ".";
		}

		if (i != 2 && i != 5) {
			EXPECT_NE(p.first, p.second);
		}
	}
}

TEST(geometry_cir, inter_pts_lin) {
	cir c({ points[1], points[2].nr(points[1]) });

	for (unsigned int i = 2; i < points.size(); i++) {
		vector<vec> lin_pts({
			points[i], 
			points[i] + (points[i] - points[0]).rot90(),
			points[i] - (points[i] - points[0]).rot90(),
			points[i] + (points[i] - points[0]).rot90()*1.4,
			points[i] - (points[i] - points[0]).rot90()*5,
			points[i] + (points[i] - points[0]).rot90()*35,
			points[i] - (points[i] - points[0]).rot90()*.00324
		});

		for (unsigned int a = 0; a < lin_pts.size(); a++) {
			for (unsigned int b = 0; b < lin_pts.size(); b++) {
				if (a == b) continue;

				pair<vec,vec> p = c.inter_pts(lin_pts[a],lin_pts[b]);
				for (vec v : {p.first, p.second}) {
					EXPECT_NEAR(v.sq(c.c), c.r*c.r, 1e-7) << v << " should be on the border of " << c << ".";
					EXPECT_NEAR(v.cross(lin_pts[a],lin_pts[b]), 0, eps) << v << " should be collinear to " << lin_pts[a] << " " << lin_pts[b] << ".";
				}

				if (i != 2 && i != 5) {
					EXPECT_NE(p.first, p.second);
				}
			}
		}
	}
}
