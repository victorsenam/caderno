#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n;
vector<int> adj[N];

int cn_sz[N];
vector<int> cn_adj[N];

int cn_getsz (int u, int p) {
	cn_sz[u] = 1;
	for (int v : adj[u]) {
		if (p == v || cn_sz[v] == -1) continue;
		cn_sz[u] += cn_getsz(v,u);
	}
	return cn_sz[u];
}

int cn_build (int u) {
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

	cn_sz[u] = -1;
	for (int v : adj[u]) {
		if (cn_sz[v] == -1) continue;
		int w = cn_build(v);
		cn_adj[u].pb(w);
		cn_adj[w].pb(u);
	}
	return u;
}
