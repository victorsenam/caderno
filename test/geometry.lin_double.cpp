typedef double cood;
const double eps = 1e-8;

#include "gtest/gtest.h"
#include "../code/geometry.cpp"

bool operator== (vec a, vec b)
{ return (abs(a.x - b.x) < eps && abs(a.y - b.y) < eps); }

::std::ostream& operator<<(::std::ostream& os, const lin& l)
{ return os << "(" << l.a << "," << l.b << "," << l.c << ")"; }

vec get (cood x, lin l)
{ return vec(x, (l.c-l.a*x)/l.b); }
vec get (lin l, cood y)
{ return vec((l.c-l.b*y)/l.a, y); }

TEST(geometry_lin, parll) {
	for (lin l : { lin(-2, 3, 1), lin(-3, 1, 7), lin(-58, 321, 418) }) {
		for (vec v : { vec(100,-50), vec(-150,50), vec(-150,150), vec(-20,160), vec(50,0), vec(-.5,0) }) {
			lin m = l.parll(v);
			vec a = get(0,l) - get(1,l);
			vec b = get(0,m) - get(1,m);

			EXPECT_NEAR(a^b, 0, 1e-8) << "General line " << l << ". Parallel " << m << " through " << v << " is parallel. Got " << a << " and " << b << ".";
			EXPECT_NEAR(get(v.x,m).y, v.y, 1e-8) << "General line " << l << ". Parallel " << m << " through " << v << " passes through it. Got " << get(v.x,l) << ".";
			EXPECT_NEAR(get(m,v.y).x, v.x, 1e-8) << "General line " << l << ". Parallel " << m << " through " << v << " passes through it. Got " << get(l,v.y) << ".";
		}
	}

	for (lin l : { lin(2, 0, 1), lin(4, 0, 7) }) {
		for (vec v : { vec(4, 0), vec(4, 23), vec(7, 41), vec(41, 0) }) {
			lin m = l.parll(v);
			vec a = get(l,0) - get(l,1);
			vec b = get(m,0) - get(m,1);

			EXPECT_NEAR(a^b, 0, 1e-8) << "Vertical line " << l << ". Parallel " << m << " through " << v << " is parallel. Got " << a << " and " << b << ".";
			EXPECT_NEAR(get(m,v.y).x, v.x, 1e-8) << "Vertical line " << l << ". Parallel " << m << " through " << v << " passes through it. Got " << get(v.x,l) << ".";
		}
	}

	for (lin l : { lin(0, 2, 1), lin(0, 4, 7) }) {
		for (vec v : { vec(4, 0), vec(4, 23), vec(7, 41), vec(41, 0) }) {
			lin m = l.parll(v);
			vec a = get(0,l) - get(1,l);
			vec b = get(0,m) - get(1,m);

			EXPECT_NEAR(a^b, 0, 1e-8) << "Horizontal line " << l << ". Parallel " << m << " through " << v << " is parallel. Got " << a << " and " << b << ".";
			EXPECT_NEAR(get(v.x,m).y, v.y, 1e-8) << "Horizontal line " << l << ". Parallel " << m << " through " << v << " passes through it. Got " << get(l,v.y) << ".";
		}
	}
}

TEST(geometry_lin, perp) {
	for (lin l : { lin(-2, 3, 1), lin(-3, 1, 7), lin(-58, 321, 418) }) {
		lin m = l.perp();
		vec a = get(0,l) - get(1,l);
		vec b = get(0,m) - get(1,m);

		EXPECT_NEAR(a*b, 0, 1e-8) << "General line " << l << ". Perpendicular " << m << " is perpendicular. Got " << a << " and " << b << ".";
	}

	for (lin l : { lin(2, 0, 1), lin(4, 0, 7) }) {
		lin m = l.perp();
		vec a = get(l,0) - get(l,1);
		vec b = get(0,m) - get(1,m);

		EXPECT_NEAR(a*b, 0, 1e-8) << "Vertical line " << l << ". Perpendicular " << m << " is perpendicular. Got " << a << " and " << b << ".";
	}

	for (lin l : { lin(0, 2, 1), lin(0, 4, 7) }) {
		lin m = l.perp();
		vec a = get(0,l) - get(1,l);
		vec b = get(m,0) - get(m,1);

		EXPECT_NEAR(a*b, 0, 1e-8) << "Horizontal line " << l << ". Perpendicular " << m << " is perpendicular. Got " << a << " and " << b << ".";
	}
}

TEST(geometry_lin, inter) {
	vector<lin> lines({ lin(-2,3,1), lin(-3,1,7), lin(-58,321,418), lin(2,0,1), lin(4,0,7), lin(0,2,1), lin(0,4,7) });
	for (lin l : lines) {
		for (lin m : lines) {
			try {
				vec v = l.inter(m);

				for (lin t : {l,m}) {
					if (abs(t.a) <= eps && abs(t.b) <= eps)
					{ FAIL() << "Invalid line inputted"; }
					if (abs(t.a) > eps)
					{ EXPECT_NEAR(get(t,v.y).x, v.x, eps) << l << ".inter(" << m << ")" << v << " is in " << t << "."; }
					if (abs(t.b) > eps)
					{ EXPECT_NEAR(get(v.x,t).y, v.y, eps) << l << ".inter(" << m << ")" << v << " is in " << t << "."; }
				}
			} catch (int e) {
				int cnt = 0;
				for (vec a : { get(l,0) - get(l,1), get(0,l) - get(1,l) }) {
					if (abs(a.x) == 1./0. || a.x != a.x || abs(a.y) == 1./0. || a.y != a.y) continue;
					for (vec b : { get(m,0) - get(m,1), get(0,m) - get(1,m) }) {
						if (abs(b.x) == 1./0. || b.x != b.x ||  abs(b.y) == 1./0. || b.y != b.y) continue;
						cnt++;
						EXPECT_NEAR(a^b, 0, eps) << l << " and " << m << " are parallel. Got " << a << " and " << b << ".";
					}
				}
				if (cnt == 0)
					FAIL() << "TEST ERROR";
			}
		}
	}
}
