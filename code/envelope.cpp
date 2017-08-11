#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// typedef ll num
// const num eps = 0;

struct line {
	num a, b;

	num eval (num x) {
		return a*x + b;
	}

	bool operator < (line & ot) {
		return a > ot.a; // lines should have decreasing slope
	}
};

struct envelope {
	deque<line> qu;
	num lo, hi;

	// first point where b beats a
	num inter (line a, line b) {
		assert(!(b < a));
		
		num lo = this->lo; num hi = this->hi + (eps == 0);
		while (hi - lo > eps) {
			num md = lo + (hi - lo)/2;
			if (a.eval(md) <= b.eval(md))
				lo = md + (eps == 0);
			else
				hi = md;
		}

		return lo;
	}

	void push_back (line l) {
		assert(qu.empty() || !(l < qu.back()));

		if (!qu.empty() && qu.back().eval(hi) <= l.eval(hi))
			return;

		while (qu.size() > 1) {
			num x = inter(qu.back(), l);
			if (qu[qu.size()-2].eval(x) <= qu[qu.size()-1].eval(x))
				qu.pop_back();
			else
				break;
		}

		qu.push_back(l);
	}

	void push_front (line l) {
		assert(qu.empty() || !(qu.front() < l));

		if (!qu.empty() && qu.front().eval(lo) < l.eval(lo))
			return;

		while (qu.size() > 1) {
			num x = inter(l, qu.front()) - (eps == 0);
			if (qu[0].eval(x) > qu[1].eval(x))
				qu.pop_front();
			else
				break;
		}

		qu.push_front(l);
	}

	line pop_front (num lo) {
		assert(!qu.empty() && this->lo <= lo + eps);

		this->lo = lo;
		while (qu.size() > 1 && qu[0].eval(lo) > qu[1].eval(lo))
			qu.pop_front();
		return qu.front();
	}

	line pop_back (num hi) {
		assert(!qu.empty() && this->hi >= hi - eps);

		this->hi = hi;
		while (qu.size() > 1 && qu[qu.size()-2].eval(hi) <= qu[qu.size()-1].eval(hi))
			qu.pop_back();
		return qu.back();
	}

	line get (num x) {
		assert(!qu.empty() && lo <= x + eps && x <= hi + eps);

		int lo = 0, hi = qu.size() - 1;
		while (lo < hi) {
			int md = lo + (hi - lo)/2;
			if (qu[md].eval(x) <= qu[md+1].eval(x))
				hi = md;
			else
				lo = md+1;
		}

		return qu[lo];
	}
};
