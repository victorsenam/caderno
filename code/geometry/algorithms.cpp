cir min_spanning_circle (vector<vec> v) {
	srand(time(NULL)); random_shuffle(v.begin(), v.end());
    int n = v.size(); circ c(vec(), 0);
	for (int i = 0; i < n; i++) if (!c.contains(v[i])) {
		c = circ(v[i], 0);
		for (int j = 0; j < i; j++) if (!c.contains(v[j])) {
			c = circ((v[i] + v[j])/2, abs(v[i] - v[j]) / 2);
			for (int k = 0; k < j; k++) if (!c.contains(v[k]))
				c = circ(v[i],v[j],v[k]);
		}
	}
    return c;
}
int convex_hull (vector<vec> & v, int border_in) {
	int n = v.size(); swap(v[0], *max_element(v.begin(),v.end()));
	sort(v.begin()+1, v.end(), [&v] (vec a, vec b) {
		int o = b.ccw(v[0], a);
		if (o) return (o == 1);
		return v[0].sq(a) < v[0].sq(b);
	});
	if (border_in) {
		int s = n-1;
		while (s > 1 && v[s].ccw(v[s-1],v[0]) == 0) s--;
		for (int i = s; i < n - 1 - (i - s); i++) swap(v[i], v[n-1-(i-s)]);
	}
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (s && v[s-1].x == v[i].x && v[s-1].y == v[i].y) continue;
		while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= brd) s--;
		v[s++] = v[i];
	} 
	return s;
}
double polygon_inter (vector<vec> & p, cir c) { // signed intersection area between polygon and circle
	return inner_product(p.begin(), p.end()-1, p.begin()+1, c.inter(*p.rbegin(),*p.begin()), std::plus<double>(), c.inter);
}
bool in_polygon (vector<vec> & p, vec v) { // p should be simple, borders included
	bool in = 0;
	for (int i = 0; i < p.size(); i++) {
		vec a = p[i], b = p[i?i-1:p.size()-1];
		in ^= inter_seg(a,b,v,vec(v.x,inf)) && max(a.x,b.x) > v.x + eps;
	}
	return in;
}

// if false, p[t..s] + v is the convex hull of p + v
// if true, v is inside (p[0],p[s],p[t]), s <= t and t - s is minimal
// border is considered inside, assumes convex hull excludes border points
bool in_convex_polygon (vector<vec> & p, vec v, int & s, int & t) {
	int n = p.size(); assert(n > 2);
	if (v.nr(p[0]) <= eps) { prec = succ = 0; return 1; }
	if (v.ccw(p[0],p[1]) > 0 || v.ccw(p[0],p[n-1]) < 0) { // p[0] stays
		int di = t = s = lower_bound(p.begin() + 1, p.end(), v, [&p] (vec a, vec v) {
			return v.ccw(p[0],a) >= 0;
		}) - p.begin() - 1; // last diagonal before or over this
		if (di == n-1) {
			if (v.ccw(p[0],p[n-1]) == 0 && v.ccw(p[n-2],p[n-1]) >= 0) return 1;
		} else if (di != 0) {
			t += (v.ccw(p[0],p[s]) > 0);
			if (v.ccw(p[s],p[t]) >= 0) return 1;
		}
		s = lower_bound(p.begin() + 1, p.begin() + di + 1, v, [&p] (vec & a, vec v) {
			return v.ccw(*((&a)-1),a) > 0;
		}) - p.begin() - 1; // last that stays <= di
		t = (lower_bound(p.begin() + di + 1, p.end(), -1, [&p,n] (vec & a, vec v) {
			return v.ccw(p[((&a)-(&p[0])+1)%n],a) >= 0;
		}) - p.begin())%n; // first that stays > di
	} else { // p[0] removed
		int di = lower_bound(p.begin() + 1, p.end() - 1, v, [&p] (vec a, vec v) {
			return v.ccw(p[0],a) < 0;
		}) - p.begin(); // first diagonal before of over this
		s = lower_bound(p.begin(), p.begin() + di, v, [&p] (vec & a, vec v) {
			return v.ccw(*((&a)+1),a) >= 0;
		}) - p.begin(); // first that stays < di
		t = lower_bound(p.begin() + di + 1, p.end(), -1, [&p] (vec & a, vec v) {
			return v.ccw(*((&a)-1),a) > 0;
		}) - p.begin() - 1; // last that stays >= di
	}
	return 0;
}
