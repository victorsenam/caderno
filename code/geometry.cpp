#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// NOT STANDART FROM HERE

// area de calota 2.pi.R.h (h altura)
// volume de calota pi.h/6 * (3r^2 + h^2)

// typedef ll cood;
// cood eps = 0;
// tests for double were made with eps = 1e-8

const double pi = acos(-1.);

struct vec { // vector
	// === BASIC ===
	cood x, y;
	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	vec operator * (cood o)
	{ return vec(x * o, y * o); }
	vec operator / (cood o)
	{ return vec(x / o, y / o); }
	cood operator ^ (vec o)
	{ return x * o.y - y * o.x; }
	cood operator * (vec o)
	{ return x * o.x + y * o.y; }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }
	double nr (vec o = vec())
	{ return sqrt(sq(o)); }

	cood ar (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b) // which side is this from ab? (-1 left, 0 over, 1 right)
	{ cood o = ar(a, b); return (o < -eps) - (eps < o); }

	cood pr (vec a, vec b) // norm of projection of (this)a over (this)b times norm of (this)b
	{ return (a-(*this)) * (b-(*this)); }
	int dr (vec a, vec b) // direction of (thia)a relative to (this)b (-1 opposite, 0 none, 1 same)
	{ cood o = pr(a, b); return (eps < o) - (o < -eps); }

	// === ADVANCED ===
	// rotate ccw by a (fails with ll)
	vec rotate (double a)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }

	// on which half plane is this point?
	// 0 is upper half plane (y > 0) and (x,0) where x >= 0, 1 is otherwise
	inline bool halfplane ()
	{ return (y < eps || (abs(y) <= eps && x < eps)); }

	// full ordering (ccw angle from this+(1,0), distance to this)
	// is a < b?
	// PRECISION : ok with double if norm in [-1e9,5e3]
	bool compare (vec a, vec b) {
		if ((a-(*this)).halfplane() != (b-(*this)).halfplane())
			return (b-(*this)).halfplane();
		int o = sd(a,b);
		if (o) return o < 0;
		return a.dr((*this),b) < 0;
	}

	// is this inside segment st? (tip of segment included, change for < -eps otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s, t) == 0) && !(eps < ((*this) - s) * ((*this) - t)); }

	// which range of points does this point remove from a convex polygon
	// answer as an open range, it removes ]first..second[
	// considers points in border as not in polygon
	// p should be a vector with [0..n-1]
	pii convex_cover (vec v[], int n, const vector<int> & p) {
		if (nr(v[0]) <= eps)
			return pii(n-1,1);
		// i'm taking advantage of lower_bound
		// it returns the first position where compare is false

		// does this point remove 0?
		// be careful adapting this condition for points in border considered in polygon
		if (sd(v[0],v[1]) < 0 || sd(v[n-1],v[0]) < 0) {
			// first diagonal to the left of this
			int di = lower_bound(p.begin()+1, p.end(), -1, [this,v] (int i, int j) {
				assert(j == -1);
				return sd(v[0],v[i]) <= 0;
			}) - p.begin();
			// we know di is removed

			// last vertex not removed before di
			int lo = lower_bound(p.begin()+1, p.begin()+di, -1, [this,v] (int i, int j) {
				assert(j == -1);
				return sd(v[i-1],v[i]) < 0;
			}) - p.begin() - 1;

			// first vertex not removed after di
			int hi = lower_bound(p.begin()+di, p.end(), -1, [this,v,n] (int i, int j) {
				assert(j == -1);
				return sd(v[(i+1)%n],v[i]) <= 0;
			}) - p.begin();

			return pii(lo%n,hi%n);
		// now 0 is removed
		} else {
			// last diagonal to the left (or over) this
			int di = lower_bound(p.begin()+1, p.end(), -1, [this,v] (int i, int j) {
				assert(j == -1);
				return sd(v[0],v[i]) >= 0;
			}) - p.begin() - 1;
			// we know di is not removed

			// first vertex not removed before di
			int lo = lower_bound(p.begin(), p.begin()+di, -1, [this,v] (int i, int j) {
				assert(j == -1);
				return sd(v[i+1],v[i]) <= 0;
			}) - p.begin();

			// last vertex not removed after di
			int hi = lower_bound(p.begin()+di+1, p.end(), -1, [this,v] (int i, int j) {
				assert(j == -1);
				return sd(v[i-1],v[i]) < 0;
			}) - p.begin() - 1;

			return pii(hi%n,lo%n);
		}
	}
};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }

// tests TODO
struct lin { // line
	cood a, b, c;

	lin () {}
	lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}

	// parallel to this through p
	lin parll (vec p) { return lin(a, b, a * p.x + b * p.y); }

	// line intersection
	vec inter (lin o) {
		cood d = a * o.b - o.a * b;
		if (d < eps && -eps < d) throw 0; // parallel
		return vec((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
	}
};

// tests TODO
// returns any point on the intersection of ab and cd (including all tips)
bool seg_inter (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		return true;
	return (c.sd(a, b) * d.sd(a, b) == -1 && a.sd(c, d) * b.sd(c, d) == -1);
}

// brd = do points on the border belong to convex?
// computes convex hull of given vector (inplace)
// returns size of convex hull
int graham (vec v[], int n, int brd) {
	for (int i = 1; i < n; i++) {
		if (v[i].x < v[0].x || (v[i].x == v[0].x && v[i].y < v[0].y))
			swap(v[0], v[i]);
	}

	sort(v+1, v+n, [v] (vec a, vec b) {
		int o = b.sd(v[0], a);
		if (o) return (o == -1);
		return v[0].sq(a) < v[0].sq(b);
	});

	if (brd) {
		int s = n-1;
		while (s > 1 && v[s].sd(v[s-1],v[0]) == 0)
			s--;
		for (int i = s; i < n - 1 - (i - s); i++)
			swap(v[i], v[n-1-(i-s)]);
	}

	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && v[s-1].x == v[i].x && v[s-1].y == v[i].y) continue;
		while (s >= 2 && v[s-1].sd(v[s-2],v[i]) <= -brd)
			s--;
		v[s++] = v[i];
	}

	return s;
}
