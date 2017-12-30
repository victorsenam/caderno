// area de calota na altura h : 2.pi.R.h
// volume de calota na altura h : pi.h/6 * (3r^2 + h^2)

// XXX marks risky behaviour and TODO marks untested functions
// typedef double cood; cood eps = 1e-8; cood inf = 1./0.;
const double pi = acos(-1.);
inline ll sq (ll x) { return x*x; }
inline double sq (double x) { return x*x; }
struct vec { // vector
	cood x, y;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline vec operator - (vec o) { return vec(x - o.x, y - o.y); }
	inline vec operator + (vec o) { return vec(x + o.x, y + o.y); }
	inline vec operator * (cood o) { return vec(x * o, y * o); }
	inline vec operator / (cood o) { return vec(x / o, y / o); }
	inline cood operator ^ (vec o) { return x * o.y - y * o.x; }
	inline cood operator * (vec o) { return x * o.x + y * o.y; }

	inline cood cross (vec a, vec b) { return ((*this)-a) ^ ((*this)-b); } // |(this)a|sen(angle)
	inline cood inner (vec a, vec b) { return ((*this)-a) * ((*this)-b); } // |(this)a|cos(angle)
	inline double angle (vec a, vec b) { return atan2(cross(a,b),inner(a,b)); } // ccw angle from (this)a to (this)b in range [-pi,pi]
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); } // this is to the (1 left, 0 over, -1 right) of ab
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); } // a(this) is to the (1 same, 0 none, -1 opposite) direction of ab
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); }
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); } // ccw by a radians
	inline vec rot90 () { return vec(-y,x); } // rotate(pi/2)

	inline bool operator < (const vec & o) const { return (x != o.x)?(x < o.x):(y > o.y); } // lex compare (inc x, dec y)
	// full ccw angle from compare beginning upwards (this+(0,1)) around (*this)
	// incresing distance on ties
	bool compare (vec a, vec b) { 
		if ((a < (*this)) != (b < (*this))) return a < (*this);
		int o = ccw(a,b); if (o) return o > 0;
		return a.dir((*this),b) < 0;
	}

	bool in_seg (vec a, vec b) { return ccw(a,b) == 0 && dir(a,b) <= 0; } // tips included
	double dist2_lin (vec a, vec b) { return double(::sq(cross(a,b)))/a.sq(b); } // see cir.has_inter_lin
	double dist2_seg (vec a, vec b) { return a.dir((*this),b) == (b.dir((*this),a)) ? dist2_lin(a,b) : min(sq(a),sq(b)); }
};
struct lin { // line
	cood a, b, c; // a*x + b*y = c
	lin () {} lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}
	inline lin parll (vec p) { return lin{a, b, a*p.x + b * p.y}; }
	inline lin perp () { return lin{-b, a, c}; }
	vec inter (lin o) {
		cood d = a * o.b - o.a * b;
		if (-eps <= d && d <= eps) throw 1; // parallel
		return vec((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
	}
	bool contains (vec v) { return abs(a*v.x + b*v.y - c) <= eps; }
	vec at_x (cood x) { return vec(x,(c-a*x)/b); }
	vec at_y (cood y) { return vec((c-b*y)/a,y); }
};
struct cir { // circle
	vec c; cood r;
	cir () {} cir (vec v, cood d) : c(v), r(d) {}
	cir (vec u, vec v, vec w) {
		vec mv = (u+v)/2; lin s(mv, mv+(v-u).rot90());
		vec mw = (u+w)/2; lin t(mw, mw+(w-u).rot90());
		c = s.inter(t); r = c.nr(u);
	}
	inline bool contains (vec w) { return c.sq(w) <= sq(r) + eps; } // border included
	inline bool has_inter (cir o) { return c.sq(o.c) <= sq(r + o.r) + eps; } // borders included
	inline bool has_border_inter (cir o) { return has_inter(o) && c.sq(o.c) + eps >= sq(r - o.r); }
	inline bool has_inter_lin (vec a, vec b) { return sq(c.cross(a,b)) <= sq(r)*a.sq(b) + eps; } // borders included XXX overflow
	inline bool has_inter_seg (vec a, vec b) { return has_inter_lin(a,b) && (contains(a) || contains(b) || a.dir(c,b)*b.dir(c,a) != -1); } // borders and tips included XXX overflow
	inline double arc_area (vec a, vec b) { return c.angle(a,b)*r*r/2; } // smallest arc, ccw positive
	inline double arc_len (vec a, vec b) { return c.angle(a,b)*r; } // smallest arc, ccw positive
	pair<vec,vec> border_inter (cir o) {
		if (!has_border_inter(o)) throw 0;
		double a = (sq(r) + o.c.sq(c) - sq(o.r))/(2*o.c.nr(c));
		vec v = (o.c - c)/o.c.nr(c); vec m = c + v * a;
		double h = sqrt(sq(r) - sq(a)); h = h!=h?0:h;
		return pair<vec,vec>(m + v.rot90()*h, m - v.rot90()*h);
	}
	pair<vec,vec> border_inter_lin (vec a, vec b) { // first is closest to a than second
		if (a.dir(b,c) == -1) swap(a,b);
		if (!has_inter_lin(a,b)) throw 0;
		double d2 = c.dist2_lin(a,b); vec p = (b-a)/a.nr(b);
		double h = sqrt(r*r - d2); h = h!=h?0:h; 
		double y = sqrt(c.sq(a) - d2); y = y!=y?0:y;
		return pair<vec,vec>(a + p*(y-h), a + p*(y+h));
	}
	double triang_inter (vec a, vec b) { // ccw oriented, this with (c,a,b) TODO
		double res = 0.; bool inv = 0; pair<vec,vec> itr = border_inter_lin(a,b);
		if (contains(b)) { swap(a,b); inv = 1; }
		if (contains(b)) res = c.cross(a,b)/2;
		else if (contains(a)) res = c.cross(a,itr.first)/2 + arc_area(itr.first,b);
		else if (has_inter_seg(a,b)) res = arc_area(a,itr.first) + c.cross(itr.first,itr.second)/2 + arc_area(itr.second,b);
		else res = arc_area(a,b);
		return inv?-res:res;
	}
};
bool inter_seg (vec a, vec b, vec c, vec d) { // tips included TODO
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b)) return true;
	return (c.ccw(a, b) * d.ccw(a, b) == -1 && a.ccw(c, d) * b.ccw(c, d) == -1);
}
double dist2_seg (vec a, vec b, vec c, vec d){return inter_seg(a,b,c,d)?0.:min({ a.dist2_seg(c,d), b.dist2_seg(c,d), c.dist2_seg(a,b), d.dist2_seg(a,b) });} // TODO
ostream& operator<<(ostream& os, vec o) { return os << '(' << o.x << ", " << o.y << ')'; }
ostream& operator<<(ostream& os, lin o) { return os << '[' << o.a << "x + " << o.b << "y = " << o.c << ']'; }
ostream& operator<<(ostream& os, cir o) { return os << '[' << o.c << o.r << ']'; }
