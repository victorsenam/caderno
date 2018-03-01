// typedef ll num; const num eps = 0; num INF = 1e17;
// XXX double: indicates operations specific to integers (+1,lo<hi,...), non precision-related
template<typename line> struct envelope { // if line is used, the template tag can be simply removed
	deque<line> q; num lo,hi; envelope (num _lo, num _hi) : lo(_lo), hi(_hi) {}
	void push_front (line l) { assert(q.empty() || !(q.front()<l)); // l is best at lo or never
		if (!q.empty() && q.front()(lo) < l(lo)) return;
		for (num x; q.size(); q.pop_front()) {
			x = (q.size()<=1?hi:min(max(lo,q.front().inter(*next(q.begin()))-1),hi+1));
			if (l(x) > q.front()(x)) break;
		}
		q.push_front(l);
	}
	void push_back (line l) { assert(q.empty() || !(l<q.back())); // l is best at hi or never
		if (!q.empty() && q.back()(hi) <= l(hi)) return;
		for (num x; q.size(); q.pop_back()) {
			x = (q.size()<=1?lo:min(max(lo,next(q.rbegin())->inter(q.back())),hi+1));
			if (l(x) >= q.back()(x)) break;
		}
		q.push_back(l);
	}
	void pop_front (num _lo) { assert(lo<=_lo+eps); for(lo=_lo;q.size()>1&&q.front()(lo)>(*next(q.begin()))(lo);q.pop_front()); } // always amort. O(1)
	void pop_back (num _hi) { assert(hi>=_hi-eps); for(hi=_hi;q.size()>1&&(*next(q.rbegin()))(hi)<=q.back()(hi);q.pop_back()); } // always amort. O(1)
	line get (num x) { return (*lower_bound(q.begin(),q.end()-1,q.front(),[x](line & a, const line & o){ return a(x)>(*((&a)+1))(x); })); } // always O(lg(n))
};
struct line { // env operations in amort. O(1)
	num a,b; num operator () (num x) const { return a*x+b; }
	bool operator < (const line & ot) const { return a>ot.a; } // decreasing slope, if function ties, envelope gets minimum here
	num inter (line o) { assert(!(o<(*this))); return (o.a==a)?((b<o.b)?INF:-INF):(o.b-b-(o.b-b<0)*(a-o.a-1))/(a-o.a) + 1; }
};
struct generic_line { // change only parameters and () for any viable functions, env operations in amort. O(lg(hi-lo))
	envelope<generic_line> & env; num a,b; num operator () (num x) const { return a*x+b; }
	bool operator < (const generic_line & ot) const { return (*this)(env.lo) < ot(env.lo) && (*this)(env.hi) > ot(env.hi); } // first element is best at lo
	num inter (generic_line o) { assert(!(o<(*this)));
		num lo = env.lo; num hi = env.hi+1;
		while (lo < hi) {
			num md = lo+(hi-lo)/2;
			if ((*this)(md)<=o(md)) lo = md+1;
			else hi = md;
		}
		return lo;
	}
};
template<typename line> struct full_envelope {
	vector<envelope<line> > v; full_envelope(envelope<line> c) : v({c}) {}
	void add (line l) { // amort. O(lg(n)*inter)
		envelope<line> nw(v[0].lo,v[0].hi); nw.push_back(l);
		while (v.size() && v.back().q.size() <= nw.q.size()) {
			envelope<line> aux(nw.lo,nw.hi); auto jt = nw.q.begin();
			for (line r : v.back().q) {
				while (jt != nw.q.end() && *jt < r) aux.push_back(*(jt++));
				aux.push_back(r);
			}
			while (jt != nw.q.end()) aux.push_back(*(jt++));
			nw = aux; v.pop_back();
		}
		v.push_back(nw);
	}
	line get (num x) { // O(lg(n)^2) use pop_back/pop_front for better time
		line b = v.front().get(x);
		for (int i = 1; i < (int) v.size(); i++) {
			line c = v[i].get(x);
			if (c(x)!=b(x)?c(x)<b(x):c<b) b = c;
		}
		return b;
	}
};
