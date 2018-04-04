//typedef int val; // type of flow
//typedef int num; // type of cost
//const int N = ; const int M =  * 2; const val eps = 0;
struct cycle_cancel {
	int hd[N], seen[N], qu[N], lv[N], ei[N], to[M], nx[M], ct[N], pai[N]; val fl[M], cp[M], flow; num cs[M], d[N], tot; int en = 2, n; int tempo = 0;
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
	val dfs(int s, int t, val f) {
		if(s == t) return f;
		for(int &e = ei[s]; e; e = nx[e]) if(ei[to[e]] && seen[to[e]] == tempo && cp[e] - fl[e] > eps && lv[to[e]] == lv[s] - 1)
			if(val rf = dfs(to[e], t, min(f, cp[e] - fl[e]))) {
				fl[e] += rf;
				fl[e ^ 1] -= rf;
				return rf;
			}
		return 0;
	}
	bool spfa() {
		tempo++; int a = 0, b = 0, u;
		for(int i = 0; i < n; i++) { d[i] = 0; qu[b++] = i; seen[i] = tempo; ct[i] = 0; }
		while(a != b) {
			u = qu[a++]; if(a == N) a = 0; seen[u] = 0;
			if(ct[u]++ >= n + 1) { a--; break; }
			for(int e = hd[u]; e; e = nx[e]) if(cp[e] - fl[e] > val(0) && d[u] + cs[e] < d[to[e]] - eps) {
				d[to[e]] = d[u] + cs[e]; pai[to[e]] = e ^ 1;
				if(seen[to[e]] < tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
			}
		}
		if(a == b) return false;
		val mn = numeric_limits<val>::max();
		tempo++;
		for(; seen[u] != tempo; u = to[pai[u]]) seen[u] = tempo;
		for(int v = u; seen[v] != tempo + 1; v = to[pai[v]]) {
			seen[v] = tempo + 1;
			mn = min(mn, cp[pai[v] ^ 1] - fl[pai[v] ^ 1]);
		}
		for(int v = u; seen[v] == tempo + 1; v = to[pai[v]]) {
			seen[v] = 0;
			fl[pai[v]] -= mn;
			fl[pai[v] ^ 1] += mn;
		}
		return true;
	}
	val max_flow(int s, int t) {
		val fl = 0;
		while (bfs(s, t)) for(val f; (f = dfs(s, t, numeric_limits<val>::max())); fl += f);
		return fl;
	}
	// public $
	num min_cost(int s, int t) {
		flow = max_flow(s, t);
		while(spfa());
		tot = 0;
		for(int i = 2; i < en; i++)
			if(fl[i] > 0)
				tot += fl[i] * cs[i];
		return tot;
	}
	void reset_flow() { memset(fl, 0, sizeof(val) * en); }
	void add_edge(int u, int v, val c, num s) {
		fl[en] = 0; cp[en] = c; to[en] = v; nx[en] = hd[u]; cs[en] =  s; hd[u] = en++;
		fl[en] = 0; cp[en] = 0; to[en] = u; nx[en] = hd[v]; cs[en] = -s; hd[v] = en++;
	}
	void init(int n) { this->n = n; en = 2; memset(hd, 0, sizeof(int) * n); } // XXX must be called
};
