#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n;
vector<int> adj[N];

int cn_sz[N];
int cn_dep[N]; // depth on cent tree
int cn_dist[20][N]; // distance to centroid antecessor with given depth
vector<int> cn_adj[N];

int cn_getsz (int u, int p) {
	cn_sz[u] = 1;
	for (int v : adj[u]) {
		if (p == v || cn_sz[v] == -1) continue;
		cn_sz[u] += cn_getsz(v,u);
	}
	return cn_sz[u];
}

void cn_setdist (int u, int p, int depth, int dist) { // not essential
	cn_dist[depth][u] = dist;
	for (int v : adj[u]) {
		if (p == v || cn_sz[v] == -1) continue;
		cn_setdist(v, u, depth, dist+1);
	}
}

int cn_build (int u, int depth) {
	int siz = cn_getsz(u,u);
	int w = u;
	do {
		u = w;
		for (int v : adj[u]) {
			if (cn_sz[v] == -1 || cn_sz[v] >= cn_sz[u] || cn_sz[v] + cn_sz[v] < siz)
				continue;
			w = v;
		}
	} while (u != w);

	cn_setdist(u,u,depth,0); // not essential
	cn_sz[u] = -1;
	cn_dep[u] = depth;

	for (int v : adj[u]) {
		if (cn_sz[v] == -1) continue;
		int w = cn_build(v, depth+1);
		cn_adj[u].pb(w); // not essential
		cn_adj[w].pb(u); // not essential
	}
	return u;
}
