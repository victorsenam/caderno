namespace mincost {
// const int N = , M =  * 2; const num eps = 0;
typedef int val; // type of flow
typedef int num; // type of cost
int es[N], to[M], nx[M], en, pai[N], seen[N], tempo, qu[N];
val fl[M], cp[M], flow; num cs[M], d[N], tot;
val spfa(int s, int t) {
	tempo++; int a = 0, b = 0;
	for(int i = 0; i < N; i++) d[i] = numeric_limits<num>::max();
	d[s] = 0; qu[b++] = s; seen[s] = tempo;
	while(a != b) {
		int u = qu[a++]; if(a == N) a = 0; seen[u] = 0;
		for(int e = es[u]; e != -1; e = nx[e]) if(cp[e] - fl[e] > val(0) && d[u] + cs[e] < d[to[e]] - eps) {
			d[to[e]] = d[u] + cs[e]; pai[to[e]] = e ^ 1;
			if(seen[to[e]] < tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
		}
	}
	if(d[t] == numeric_limits<num>::max()) return false;
	val mx = numeric_limits<val>::max();
	for(int u = t; u != s; u = to[pai[u]])
		mx = min(mx, cp[pai[u] ^ 1] - fl[pai[u] ^ 1]);
	tot += d[t] * val(mx);
	for(int u = t; u != s; u = to[pai[u]])
		fl[pai[u]] -= mx, fl[pai[u] ^ 1] += mx;
	return mx;
}
void init(int n) { en = 0; memset(es, -1, sizeof(int) * n); } // XXX should be called before mncost
num mncost(int s, int t) {
	tot = 0; flow = 0;
	while(val a = spfa(s, t)) flow += a;
	return tot;
}
void add_edge(int u, int v, val c, num s) {
	fl[en] = 0; cp[en] = c; to[en] = v; nx[en] = es[u]; cs[en] =  s; es[u] = en++;
	fl[en] = 0; cp[en] = 0; to[en] = u; nx[en] = es[v]; cs[en] = -s; es[v] = en++;
}
}
