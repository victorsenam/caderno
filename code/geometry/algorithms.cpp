cir min_spanning_circle (vec * v, int n) { // n
	srand(time(NULL)); random_shuffle(v, v+n); cir c(vec(), 0); int i,j,k;
	for (i = 0; i < n; i++) if (!c.contains(v[i]))
		for (c = cir(v[i],0), j = 0; j < i; j++) if (!c.contains(v[j]))
			for (c = cir((v[i] + v[j])/2,v[i].nr(v[j])/2), k = 0; k < j; k++) if (!c.contains(v[k]))
					c = cir(v[i],v[j],v[k]);
	return c;
}//$
int convex_hull (vec * v, int n, int border_in) { // nlg | border_in (should border points stay?)
	swap(v[0], *min_element(v,v+n)); int s, i;
	sort(v+1, v+n, [&v] (vec a, vec b) { int o = b.ccw(v[0], a); return (o?o==1:v[0].sq(a)<v[0].sq(b)); });
	if (border_in) {
		for (s = n-1; s > 1 && v[s].ccw(v[s-1],v[0]) == 0; s--);
		reverse(v+s, v+n);
	}
	for (i = s = 0; i < n; i++) if (!s || !(v[s-1] == v[i])) {
		for (; s >= 2 && v[s-1].ccw(v[s-2],v[i]) >= border_in; s--);
		swap(v[s++],v[i]);
	}
	return s;
}//$
int monotone_chain (vec * v, int n, int border_in) { // nlg | border_in (should border points stay?)
	vector<vec> r; sort(v, v+n); n = unique(v, v+n) - v;
	for (int i = 0; i < n; r.pb(v[i++])) while (r.size() >= 2 && r[r.size()-2].ccw(r.back(),v[i]) <= -border_in) r.pop_back();
	r.pop_back(); unsigned int s = r.size();
	for (int i = n-1; i >= 0; r.pb(v[i--])) while (r.size() >= s+2 && r[r.size()-2].ccw(r.back(),v[i]) <= -border_in) r.pop_back();
	return copy(r.begin(), r.end() - (r.size() > 1), v) - v;
}//$
double polygon_inter (vec * p, int n, cir c) { // signed area
	return inner_product(p, p+n-1, p+1, c.triang_inter(p[n-1],p[0]), std::plus<double>(), [&c] (vec a, vec b) { return c.triang_inter(a,b); });
}//$
int polygon_pos (vec * p, int n, vec v) { // lg | p should be simple (-1 out, 0 border, 1 in)
	int in = -1; // it's a good idea to randomly rotate the points in the double case, numerically safer
	for (int i = 0; i < n; i++) {
		vec a = p[i], b = p[i?i-1:n-1]; if (a.x > b.x) swap(a,b);
		if (a.x + eps <= v.x && v.x < b.x + eps) { in *= v.ccw(a,b); }
		else if (v.in_seg(a,b)) { return 0; }
	}
	return in;
}//$
int polygon_pos_convex (vec * p, int n, vec v) { // lg(n) | (-1 out, 0 border, 1 in) TODO 
	if (v.sq(p[0]) <= eps) return 0;
	if (n <= 1) return 0; if (n == 2) return v.in_seg(p[0],p[1])?0:-1;
	if (v.ccw(p[0],p[1]) < 0 || v.ccw(p[0],p[n-1]) > 0) return -1;
	int di = lower_bound(p+1,p+n-1,v, [&p](vec a,vec v) { return v.ccw(p[0],a) > 0; }) - p;
	if (di == 1) return v.ccw(p[1],p[2]) >= 0?0:-1;
	return v.ccw(p[di-1],p[di]);
}//$
// v is the pointset, w is auxiliary with size at least equal to v's
cood closest_pair (vec * v, vec * w, int l, int r, bool sorted = 0) { // nlg | r is exclusive TODO (AC on cf, no test)
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
}//$
double union_area (cir * v, int n) { // n^2lg | XXX joins equal circles TODO (AC on szkopul, no tests)
	struct I { vec v; int i; } c[2*(n+4)];
	srand(time(NULL)); cood res = 0; vector<bool> usd(n);
	cood lim = 1./0.; for (int i = 0; i < n; i++) lim = min(lim, v[i].c.y - v[i].r - 1);
	for (int i = 0, ss = 0; i < n; i++, ss = 0) {
		vec fp = v[i].c + vec(0,v[i].r).rotate(rand()); // rotation avoids corner on cnt initialization
		int cnt = 0, eq = 0; 
		for (int j = 0; j < n; j++) {
			cnt += (usd[j] = v[j].contains(fp));
			if (!v[i].has_border_inter(v[j])) continue;
			if (v[i].c == v[j].c) eq++;
			else {
				pair<vec,vec> r = v[i].border_inter(v[j]);
				c[ss++] = {r.first, j}; c[ss++] = {r.second, j};
			}
		}
		vec d = vec(v[i].r,0); for (int k = 0; k < 4; k++, d = d.rot90()) c[ss++] = {v[i].c + d, i};
		int md = partition(c,c+ss,[v,i,fp](I a){return a.v.ccw(v[i].c,fp) > 0;}) - c;
		sort(c,c+md,[v,i](I a,I b){return a.v.ccw(v[i].c,b.v) < 0;});
		sort(c+md,c+ss,[v,i](I a,I b){return a.v.ccw(v[i].c,b.v) < 0;});
		for (int j = 0; j < ss; j++) {
			if (c[j].i != i) { cnt -= usd[c[j].i]; usd[c[j].i] = !usd[c[j].i]; cnt += usd[c[j].i]; }
			vec a = c[j].v, b = c[(j+1)%ss].v;
			cood cir = abs(v[i].arc_area(a,b) - v[i].c.cross(a,b)/2), tra = abs((b.x-a.x)*(a.y+b.y-2*lim)/2);
			cood loc = (a.x<b.x)?cir-tra:tra+cir; res += (cnt==eq)?loc/eq:0;
		}
	}
	return res;
}//$
pii antipodal (vec * p, int n, vec v) { // lg(n) | extreme segments relative to direction v TODO
	// po: closest to dir, ne: furthest from dir
	bool sw = ((p[1]-p[0])*v < 0);
	if (sw) v = vec(0,0) - v; // lower_bound returns the first such that lambda is false
	int md = lower_bound(p+1, p+n, v, [p] (vec & a, vec v) { return (a-p[0])*v > eps; }) - p; // chain separation
	int po = lower_bound(p, p+md-1, v, [p,n] (vec & a, vec v) { return (p[(&a+1-p)%n]-a)*v > eps; }) - p; // positive
	int ne = (lower_bound(p+md, p+n, v, [p,n] (vec & a, vec v) { return (p[(&a+1-p)%n]-a)*v <= eps; }) - p)%n; // negative
	if (sw) swap(po,ne);
	return pii(po,ne);
}//$
int mink_sum (vec * a, int n, vec * b, int m, vec * r) { // (n+m) | a[0]+b[0] should belong to sum, doesn't create new border points TODO
	if (!n || !m) return 0; int i, j, s; r[0] = a[0] + b[0];
	for (i = 0, j = 0, s = 1; i < n || j < m; s++) {
		if (i >= n) j++;
		else if (j >= m) i++;
		else {
			int o = (a[(i+1)%n]+b[j%m]).ccw(r[s-1],a[i%n]+b[(j+1)%m]);
			j += (o >= 0); i += (o <= 0);
		}
		r[s] = a[i%n] + b[j%m];
	}
	return s-1;
}//$
int inter_convex (vec * p, int n, vec * q, int m, vec * r) { // (n+m) | 
	int a = 0, b = 0, aa = 0, ba = 0, inflag = 0, s = 0;
	while ((aa < n || ba < m) && aa < n+n && ba < m+m) {
		vec p1 = p[a], p2 = p[(a+1)%n], q1 = q[b], q2 = q[(b+1)%m];
		vec A = p2 - p1, B = q2 - q1;
		int cross = vec(0,0).ccw(A,B), ha = p1.ccw(p2,q2), hb = q1.ccw(q2,p2);
		if (cross == 0 && p2.ccw(p1,q1) == 0 && A*B < -eps) {
			if (q1.in_seg(p1,p2)) r[s++] = q1;
			if (q2.in_seg(p1,p2)) r[s++] = q2;
			if (p1.in_seg(q1,q2)) r[s++] = p1;
			if (p2.in_seg(q1,q2)) r[s++] = p2;
			if (s < 2) return s;
			inflag = 1; break;
		} else if (cross != 0 && inter_seg(p1,p2,q1,q2)) {
			if (inflag == 0) aa = ba = 0;
			r[s++] = lin(p1,p2).inter(lin(q1,q2));
			inflag = (hb > 0) ? 1 : -1;
		}
		if (cross == 0 && hb < 0 && ha < 0) return s;
		bool t = cross == 0 && hb == 0 && ha == 0;
		if (t ? (inflag == 1) : (cross >= 0) ? (ha <= 0) : (hb > 0)) {
			if (inflag == -1) r[s++] = q2;
			ba++; b++; b %= m;
		} else {
			if (inflag == 1) r[s++] = p2;
			aa++; a++; a %= n;
		}
	}
	if (inflag == 0) {
		if (polygon_pos_convex(q,m,p[0]) >= 0) { copy(p, p+n, r); return n; }
		if (polygon_pos_convex(p,n,q[0]) >= 0) { copy(q, q+m, r); return m; }
	}
	s = unique(r, r+s) - r;
	if (s > 1 && r[0] == r[s-1]) s--;
	return s;
}
