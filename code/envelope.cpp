// typedef ll num; const num eps = 0;
// XXX double: indicates operations specific to integers, not precision related
template<typename line> struct envelope {
	deque<line> q; num lo,hi; envelope (num _lo, num _hi) : lo(_lo), hi(_hi) {}
	void push_front (line l) { // amort. O(inter) | l is best at lo or never
		if (q.size() && q[0](lo) < l(lo)) return;
		for (num x; q.size(); q.pop_front()) {
			x = (q.size()<=1?hi:q[0].inter(q[1],lo,hi)-1); // XXX double (-1)
			if (l(x) > q[0](x)) break;
		}
		q.push_front(l);
	}
	void push_back (line l) { // amort. O(inter) | l is best at hi or never
		if (q.size() && q[q.size()-1](hi) <= l(hi)) return;
		for (num x; q.size(); q.pop_back()) {
			x = (q.size()<=1?lo:q[q.size()-2].inter(q[q.size()-1],lo,hi));
			if (l(x) >= q[q.size()-1](x)) break;
		}
		q.push_back(l);
	}
	void pop_front (num _lo) { for (lo=_lo; q.size()>1 && q[0](lo) > q[1](lo); q.pop_front()); } // amort. O(n)
	void pop_back (num _hi) { for (hi=_hi; q.size()>1 && q[q.size()-2](hi) <= q[q.size()-1](hi); q.pop_back()); } // amort. O(n)
	line get (num x) { // O(lg(R))
		int lo, hi, md; for (lo = 0, hi = q.size()-1, md = (lo+hi)/2; lo < hi; md = (lo+hi)/2)
			if (q[md](x) > q[md+1](x)) { lo = md+1; }
			else { hi = md; }
		return q[lo];
	}
};
struct line { // inter = O(1)
	num a,b; num operator () (num x) const { return a*x+b; }
	num inter (line o, num lo, num hi) { return abs(o.a-a)<=eps?((b<o.b)?hi+1:lo):min(hi+1,max(lo,(o.b-b-(o.b-b<0)*(a-o.a-1))/(a-o.a) + 1)); }
};
struct generic_line { // inter = O(lg(R))
	num a,b; num operator () (num x) const { return a*x+b; }
	num inter (generic_line o, num lo, num hi) { // first point where o strictly beats this
		for (num md = lo+((++hi)-lo)/2; lo < hi; md = lo+(hi-lo)/2) { // XXX double
			if ((*this)(md)<=o(md)) { lo = md+1; } // XXX double
			else { hi = md; }
		}
		return lo;
	}
};
template<typename line> struct full_envelope { // XXX ties are broken arbitrarily
	vector<envelope<line> > v; full_envelope(envelope<line> c) : v({c}) {} // v.reserve(30);
	void add (line l) { // amort. O(lg(n)*inter)
		envelope<line> cur(v.back().lo,v.back().hi); cur.push_back(l);
		while (!v.empty() && v.back().q.size() <= cur.q.size()) {
			deque<line> aux; swap(aux,cur.q); int i = 0, j = 0;
			for (; i < aux.size(); i++) {
				for (; j < v.back().q.size() && v.back().q[j](cur.hi) > aux[i](cur.hi); j++)
					cur.push_back(v.back().q[j]);
				cur.push_back(aux[i]);
			}
			for (; j < v.back().q.size(); j++) cur.push_back(v.back().q[j]);
			v.pop_back();
		}
		v.push_back(cur);
	}
	line get (num x) { // O(lg(n)lg(R)) | pop_back/pop_front can optimize
		line a = v[0].get(x);
		for (int i = 1; i < (int) v.size(); i++) {
			line b = v[i].get(x);
			if (b(x)<a(x)) a = b;
		}
		return a;
	}
};
