// typedef ll num; const num eps = 0;
// XXX double warnings means there's some specific integer operation (+1, lo<hi, etc...), not precision-related
struct line {
	num a, b;
	num operator () (num x) const { return a*x + b; }
	bool operator < (const line & ot) const { return a > ot.a; } // decreasing slope, if function ties, the smallest in this order is chosen
};
struct envelope { // min envelope, the first element is the best at the beggining
	deque<line> qu; num lo, hi; envelope (num a, num b) : lo(a), hi(b) {}
	num inter (line a, line b) { assert(!(b<a)); // first point where b beats (properly) a XXX double
		if (b.a == a.a) return (a.b < b.b)?hi+1:lo;
		return max(min((b.b - a.b - (b.b - a.b<0)*(a.a - b.a - 1))/(a.a - b.a) + 1,hi+1),lo);
		num lo = this->lo; num hi = this->hi + 1;
		while (lo < hi) {
			num md = lo + (hi - lo)/2;
			if (a(md) <= b(md)) lo = md+1;
			else hi = md;
		}
		return lo;
	}
	void push_back (line l) { assert(qu.empty() || !(l < qu.back())); // insert a line that is best at hi or never
		if (!qu.empty() && qu.back()(hi) <= l(hi)) return;
		for (num x; qu.size(); qu.pop_back()) {
			x = (qu.size()<=1?lo:inter(qu[qu.size()-2],qu.back()));
			if (l(x) >= qu.back()(x)) break;
		}
		qu.push_back(l);
	}
	void push_front (line l) { assert(qu.empty() || !(qu.front() < l)); // insert a line that is best at lo or never
		if (!qu.empty() && qu.front()(lo) < l(lo)) return;
		for (num x; qu.size(); qu.pop_front()) {
			x = qu.size()<=1?hi:inter(qu[0],qu[1]);
			if (l(x) > qu.front()(x)) break;
		}
		qu.push_front(l);
	}
	line pop_front (num lo) { assert(!qu.empty() && this->lo <= lo + eps); // gets best line at this new lo
		for (this->lo = lo; qu.size() > 1 && qu[0](lo) > qu[1](lo); qu.pop_front());
		return qu.front();
	}
	line pop_back (num hi) { assert(!qu.empty() && this->hi >= hi - eps); // gets best line at this new hi
		for (this->hi = hi; qu.size() > 1 && qu[qu.size()-2](hi) <= qu.back()(hi); qu.pop_back());
		return qu.back();
	}
	line get (num x) { assert(!qu.empty() && lo <= x + eps && x <= hi + eps); // gets best line at x
		return (*lower_bound(qu.begin(),qu.end()-1,qu[0],[x](line & a, const line & o){ return a(x) > (*((&a)+1))(x); }));
	}
};
struct full_envelope {
	vector<envelope> v; full_envelope(envelope c) : v({c}) {}
	void add (line l) {
		envelope nw(v[0].lo,v[0].hi); nw.push_back(l);
		while (v.size() && v.back().qu.size() <= nw.qu.size()) {
			envelope aux(nw.lo,nw.hi); auto jt = nw.qu.begin();
			for (line r : v.back().qu) {
				while (jt != nw.qu.end() && *jt < r) aux.push_back(*(jt++));
				aux.push_back(r);
			}
			while (jt != nw.qu.end()) aux.push_back(*(jt++));
			nw = aux; v.pop_back();
		}
		v.push_back(nw);
	}
	line get (num x) { // you can easily use pop_front and pop_back here
		line b = v.front().get(x);
		for (int i = 1; i < v.size(); i++) {
			line c = v[i].get(x);
			if (c(x)!=b(x)?c(x)<b(x):c<b) b = c;
		}
		return b;
	}
};
