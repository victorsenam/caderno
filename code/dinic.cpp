//typedef int num; const int N = ; const int M =  * 2; const num eps = 0;
struct dinic {
	int hd[N], seen[N], qu[N], lv[N], ei[N], to[M], nx[M]; num fl[M], cp[M]; int en = 2; int tempo = 0;
	bool bfs(int s, int t) {
		seen[t] = ++tempo; lv[t] = 0; int ql = 0, qr = 0; qu[qr++] = t;
		while(ql != qr) {
			t = qu[ql++]; ei[t] = hd[t]; if(s == t) return true;
			for(int e = hd[t]; e; e = nx[e]) if(seen[to[e]] != tempo && cp[e ^ 1] - fl[e ^ 1] > eps) {
				seen[to[e]] = tempo;
				lv[to[e]] = lv[t] + 1;
				qu[qr++] = to[e];
			}
		}
		return false;
	}
	num dfs(int s, int t, num f) {
		if(s == t) return f;
		for(int &e = ei[s]; e; e = nx[e]) if(ei[to[e]] && seen[to[e]] == tempo && cp[e] - fl[e] > eps && lv[to[e]] == lv[s] - 1)
			if(num rf = dfs(to[e], t, min(f, cp[e] - fl[e]))) {
				fl[e] += rf;
				fl[e ^ 1] -= rf;
				return rf;
			}
		return 0;
	}
	// public $
	num max_flow(int s, int t) {
		num fl = 0;
		while (bfs(s, t)) for(num f; (f = dfs(s, t, numeric_limits<num>::max())); fl += f);
		return fl;
	}
	void add_edge(int a, int b, num c, num rc=0) {
		to[en] = b; nx[en] = hd[a]; fl[en] = 0; cp[en] = c; hd[a] = en++;
		to[en] = a; nx[en] = hd[b]; fl[en] = 0; cp[en] = rc; hd[b] = en++;
	}
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }
	void init(int n=N) { en = 2; memset(hd, 0, sizeof(int) * n); } // resets all
};
