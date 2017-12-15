cir min_spanning_circle (vector<vec> & v) {
    int n = v.size();
	srand(time(NULL)); rand(); rand();
    random_shuffle(all(T));
	circ c(vec(), 0);
	for (int i = 0; i < n; i++) if (!c.contains(v[i])) {
		c = circ(v[i], 0);
		for (int j = 0; j < i; j++) if (!c.contains(v[j])) {
			c = circ((v[i] + v[j])/2, abs(v[i] - v[j]) / 2);
			for (int k = 0; k < j; k++) if (!c.contains(v[k])) {
				c = circ(v[i],v[j],v[k]);
			}
		}
	}
    return c;

}

// brd = do points on the border belong to convex?
// computes convex hull of given vector (inplace)
// returns size of convex hull
int convex_hull (vector<vec> & v, int brd) {
	int n = v.size();
	for (int i = 1; i < n; i++) {
		if (v[i].x < v[0].x || (v[i].x == v[0].x && v[i].y < v[0].y))
			swap(v[0], v[i]);
	}

	sort(v+1, v+n, [&v] (vec a, vec b) {
		int o = b.ccw(v[0], a);
		if (o) return (o == 1);
		return v[0].sq(a) < v[0].sq(b);
	});

	if (brd) {
		int s = n-1;
		while (s > 1 && v[s].ccw(v[s-1],v[0]) == 0)
			s--;
		for (int i = s; i < n - 1 - (i - s); i++)
			swap(v[i], v[n-1-(i-s)]);
	}

	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && v[s-1].x == v[i].x && v[s-1].y == v[i].y) continue;
		while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= brd)
			s--;
		v[s++] = v[i];
	}

	return s;
	
}

double polygon_inter (vector<vec> & p, cir c) {
	double res = 0;
	for (int i = 0; i < p.size(); i++)
		res += inter(p[i],p[(i+1)%p.size()]);
	return res;
}

bool in_polygon (vector<vec> & p, vec v) {

}

// is this inside (borders included) the convex polygon v of size n?
// if yes, prec is the vec that this on acw order from v[0] or 0 if there is no such
// if not, prec is the predecessor of this when added to poly and succ is the sucessor
// p should be a vector with [0..n-1]
// n should be >= 2
bool in_convex_polygon (vector<vec> & p, vec v, int & prec, int & succ) {
	int n = v.size();
	if (nr(v[0]) <= eps) {
		prec = 0;
		return 1;
	}

	if (n == 2) {
		if (in_seg(v[0],v[1]))
			return (prec = 1);

		if (ccw(v[0],v[1]) > 0) {
			prec = 1;
			succ = 0;
		} else if (ccw(v[0],v[1]) < 0) {
			prec = 0;
			succ = 1;
		} else {
			prec = succ = (v[0].dir((*this),v[1]) < 0);
		}
		return 0;
	}
	
	if (ccw(v[0],v[1]) > 0 || ccw(v[0],v[n-1]) < 0) {
	// case where v[0] is not removed
		// last diagonal before or over this
		int di = lower_bound(p.begin() + 1, p.end(), -1, [this,v] (int i, int j) {
			assert(j == -1);
			return ccw(v[0],v[i]) >= 0;
		}) - p.begin() - 1;

		// is this inside the polygon?
		prec = di;
		if (di == n-1) {
		// last segment
			if (ccw(v[0],v[n-1]) == 0 && ccw(v[n-2],v[n-1]) >= 0)
				return 1;
		} else {
		// inside otherwise
			if (ccw(v[di],v[di+1]) >= 0)
				return 1;
		}

		// last that stays before (or eq to) di
		prec = lower_bound(p.begin() + 1, p.begin() + di + 1, -1, [this,v] (int i, int j) {
			assert(j == -1);
			return ccw(v[i-1],v[i]) > 0;
		}) - p.begin() - 1;

		// first that stays after di
		succ = lower_bound(p.begin() + di + 1, p.end(), -1, [this,v,n] (int i, int j) {
			assert(j == -1);
			return ccw(v[(i+1)%n],v[i]) >= 0;
		}) - p.begin();
		if (succ == n) succ = 0;
	} else {
	// case where v[0] is removed
		// first diagonal before of over this
		// di is certainly not removed
		int di = lower_bound(p.begin() + 1, p.end() - 1, -1, [this,v] (int i, int j) {
			assert(j == -1);
			return ccw(v[0],v[i]) < 0;
		}) - p.begin();

		// first that stays (<= di)
		succ = lower_bound(p.begin(), p.begin() + di, -1, [this,v] (int i, int j) {
			assert(j == -1);
			return ccw(v[i+1],v[i]) >= 0;
		}) - p.begin();

		// last that stays (>= di)
		prec = lower_bound(p.begin() + di + 1, p.end(), -1, [this,v] (int i, int j) {
			assert(j == -1);
			return ccw(v[i-1],v[i]) > 0;
		}) - p.begin() - 1;
	}
	return 0;
}
