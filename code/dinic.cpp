//typedef int num;
//const int N = ;
//const int M =  * 2;

struct dinic {
	int hd[N], seen[N], qu[N], lv[N], ei[N], to[M], nx[M];
	num fl[M], cp[M];
	int en = 2, vn = N;
	int tempo = 0;

	// Reset the whole graph
	void reset(int n=N) { vn = n; en = 2; memset(hd, 0, sizeof(int) * vn); }
	// Reset only the flow
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }

	// edge from a to b with cap c and edge from b to a with cap rc
	void add_edge(int a, int b, int c, int rc=0) {
		to[en] = b; nx[en] = hd[a]; fl[en] = 0; cp[en] =  c; hd[a] = en++;
		to[en] = a; nx[en] = hd[b]; fl[en] = 0; cp[en] = rc; hd[b] = en++;
	}

	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * vn);
		lv[s] = 0;
		int ql = 0, qr = 0;
		qu[qr++] = s;
		while(ql != qr) {
			s = qu[ql++];
			if(s == t) return true;
			for(int e = hd[s]; e; e = nx[e])
				if(lv[to[e]] == -1 && cp[e] - fl[e] > 0) {
					lv[to[e]] = lv[s] + 1;
					qu[qr++] = to[e];
				}
		}
		return false;
	}

	num dfs(int s, int t, num f) {
		if(s == t) return f;
		seen[s] = tempo;
		for(int &e = ei[s]; e; e = nx[e])
			if(seen[to[e]] != tempo && cp[e] - fl[e] > 0 && lv[to[e]] == lv[s] + 1)
				if(num rf = dfs(to[e], t, min(f, cp[e] - fl[e]))) {
					fl[e] += rf;
					fl[e ^ 1] -= rf;
					return rf;
				}
		return 0;
	}

	num max_flow(int s, int t) {
		num fl = 0;
		while(bfs(s, t)) {
			tempo++;
			for(int i = 0; i < vn; i++) ei[i] = hd[i];
			while(num f = dfs(s, t, numeric_limits<num>::max())) {
				fl += f;
				tempo++;
			}
		}
		return fl;
	}
};
