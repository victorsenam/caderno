const int N = 1e6;

#include "gtest/gtest.h"
#include "../code/centroid.cpp"

pair<bool,pii> isBalanced (vector<int> adj[], int u, int p) {
	pii cur(1,1);

	for (int v : adj[u]) {
		if (v == p) continue;
		pair<bool,pii> nxt = isBalanced(adj, v, u);
		if (!nxt.first)
			return nxt;

		cur.first += nxt.second.first;
		cur.second = max(cur.second, nxt.second.second*2ll);
	}
	
	return pair<bool,pii>((cur.first >= cur.second),cur);
}

void setUp (int sz) {
	n = sz;
	for (int i = 0; i < n; i++) {
		cn_sz[i] = 0;
		cn_adj[i].clear();
	}
}

TEST(CentroidSimple, Path) {
	setUp(10);

	for (int i = 0; i < n; i++)
		adj[i].clear();
	for (int i = 0; i < n-1; i++) {
		adj[i].pb(i+1);
		adj[i+1].pb(i);
	}

	int u = cn_build(0);
	EXPECT_TRUE(isBalanced(cn_adj,u,u).first);

	setUp(n);
	u = cn_build(n/2);
	EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
}

TEST(CentroidSimple, Star) {
	setUp(10);

	for (int i = 0; i < n; i++)
		adj[i].clear();
	for (int i = 1; i < n; i++) {
		adj[i].pb(0);
		adj[0].pb(i);
	}

	int u = cn_build(0);
	EXPECT_TRUE(isBalanced(cn_adj,u,u).first);

	setUp(n);
	u = cn_build(n/2);
	EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
}

TEST(CentroidLarge, Path) {
	setUp(10000);

	for (int i = 0; i < n; i++)
		adj[i].clear();
	for (int i = 1; i < n; i++) {
		adj[i].pb(i-1);
		adj[i-1].pb(i);
	}

	int u = cn_build(n-1);
	EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
}

TEST(CentroidLarge, Random) {
	srand(42); rand(); rand();

	int ts = 5;

	while (ts--) {
		setUp(10000);

		for (int i = 0; i < n; i++)
			adj[i].clear();
		for (int i = 1; i < n; i++) {
			int j = rand()%i;
			adj[i].pb(j);
			adj[j].pb(i);
		}

		int u = cn_build(rand()%n);
		EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
	}
}
