cir min_spanning_circle (vec * v, int n) {
	srand(time(NULL)); random_shuffle(v, v+n); cir c(vec(), 0);
	for (int i = 0; i < n; i++) if (!c.contains(v[i])) {
		c = cir(v[i], 0);
		for (int j = 0; j < i; j++) if (!c.contains(v[j])) {
			c = cir((v[i] + v[j])/2, v[i].nr(v[j])/2);
			for (int k = 0; k < j; k++) if (!c.contains(v[k]))
				c = cir(v[i],v[j],v[k]);
		}
	}
    return c;
}
int convex_hull (vec * v, int n, int border_in) { // border_in (should border points stay?)
	swap(v[0], *min_element(v,v+n));
	sort(v+1, v+n, [&v] (vec a, vec b) {
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
		while (s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= border_in) s--;
		v[s++] = v[i];
	} 
	return s;
}
int monotone_chain (vec * v, int n, int border_in) { // border_in (should border points stay?)
	vector<vec> r; sort(v, v+n); n = unique(v, v+n) - v;
	for (int i = 0; i < n; r.pb(v[i++])) while (r.size() >= 2 && r[r.size()-2].ccw(r.back(),v[i]) <= -border_in) r.pop_back();
	r.pop_back(); unsigned int s = r.size();
	for (int i = n-1; i >= 0; r.pb(v[i--])) while (r.size() >= s+2 && r[r.size()-2].ccw(r.back(),v[i]) <= -border_in) r.pop_back();
	return copy(r.begin(), r.end() - (r.size() > 1), v) - v;
}
double polygon_inter (vec * p, int n, cir c) { // signed area
	return inner_product(p, p+n-1, p+1, c.triang_inter(p[n-1],p[0]), std::plus<double>(), [&c] (vec a, vec b) { return c.triang_inter(a,b); });
}
int polygon_pos (vec * p, int n, vec v) { // p should be simple (-1 out, 0 border, 1 in)
	int in = -1; // it's a good idea to randomly rotate the points in the double case, numerically safer
	for (int i = 0; i < n; i++) {
		vec a = p[i], b = p[i?i-1:n-1]; if (a.x > b.x) swap(a,b);
		if (a.x + eps <= v.x && v.x < b.x + eps) { in *= v.ccw(a,b); }
		else if (v.in_seg(a,b)) { return 0; }
	}
	return in;
}
int polygon_pos_convex (vec * p, int n, vec v, bool verb = 0) { // (-1 out, 0 border, 1 in) TODO 
	if (v.sq(p[0]) <= eps) return 0;
	if (verb) cout << v.ccw(p[0],p[1]) << " " << v.ccw(p[0],p[n-1]) << endl;
	if (v.ccw(p[0],p[1]) < 0 || v.ccw(p[0],p[n-1]) > 0) return -1;
	int di = lower_bound(p+1,p+n-1,v, [&p](vec a,vec v) { return v.ccw(p[0],a) > 0; }) - p;
	if (di == 1) return v.ccw(p[1],p[2]) >= 0?0:-1;
	return v.ccw(p[di-1],p[di]);
}
// v is the pointset, w is auxiliary with size at least equal to v's
cood closest_pair (vec * v, vec * w, int l, int r, bool sorted = 0) { // TODO (problem accepted, not manually tested)
	if (l + 1 >= r) return inf;
	if (!sorted) sort(v+l,v+r,[](vec a, vec b){ return a.x < b.x; });
	int m = (l+r)/2; cood x = v[m].x;
	cood res = min(closest_pair(v,w,l,m,1),closest_pair(v,w,m,r,1));
	merge(v+l,v+m,v+m,v+r,w+l,[](vec a, vec b){ return a.y < b.y; });
	for (int i = l, s = l; i < r; i++) if (sq((v[i] = w[i]).x - x) < res) {
		for (int j = s-1; j >= l && sq(w[i].y - w[j].y) < res; j--)
			res = min(res, w[i].sq(w[j]));
		w[s++] = v[i];
	}
	return res;
}
