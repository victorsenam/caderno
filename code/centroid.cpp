vector<int> adj[N]; int cn_sz[N], n;
vector<int> cn_chld[N]; int cn_dep[N], cn_dist[20][N]; // removable
void cn_setdist (int u, int p, int depth, int dist) { // removable
	cn_dist[depth][u] = dist;
	for (int v : adj[u]) if (p != v && cn_sz[v] != -1) // sz = -1 marks processed centroid (not dominated)
		cn_setdist(v, u, depth, dist+1);
}
int cn_getsz (int u, int p) {
	cn_sz[u] = 1;
	for (int v : adj[u]) if (p != v && cn_sz[v] != -1)
		cn_sz[u] += cn_getsz(v,u);
	return cn_sz[u];
}
int cn_build (int u, int depth) {
	int siz = cn_getsz(u,u); int w = u;
	do {
		u = w;
		for (int v : adj[u]) if (cn_sz[v] != -1 && cn_sz[v] < cn_sz[u] && cn_sz[v] + cn_sz[v] >= siz)
			w = v;
	} while (u != w); // u becomes current centroid root
	cn_setdist(u,u,depth,0); // removable, here you can iterate over all dominated tree
	cn_sz[u] = -1; cn_dep[u] = depth; 
	for (int v : adj[u]) if (cn_sz[v] != -1) {
		int w = cn_build(v, depth+1);
		cn_chld[u].pb(w); // removable
	}
	return u;
}
