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

bool areDistancesCorrect (vector<int> adj[], int u, int p, int f, int dist) {
	if (cn_dist[cn_dep[f]][u] != dist)
		return 0;
	for (int v : adj[u]) {
		if (p == v || cn_dep[v] < cn_dep[f])
			continue;
		if (!areDistancesCorrect(adj, v, u, f, dist+1))
			return 0;
	}
	return 1;
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

	int u = cn_build(0,0);
	EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
	for (int i = 0; i < n; i++)
		EXPECT_TRUE(areDistancesCorrect(adj,i,i,i,0)) << "Centroid calculates distances to antecessors of node " << i << " correctly";

	setUp(n);
	u = cn_build(n/2,0);
	EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
	for (int i = 0; i < n; i++)
		EXPECT_TRUE(areDistancesCorrect(adj,i,i,i,0)) << "Centroid calculates distances to antecessors of node " << i << " correctly";
}

TEST(CentroidSimple, Star) {
	setUp(10);

	for (int i = 0; i < n; i++)
		adj[i].clear();
	for (int i = 1; i < n; i++) {
		adj[i].pb(0);
		adj[0].pb(i);
	}

	int u = cn_build(0,0);
	EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
	for (int i = 0; i < n; i++)
		EXPECT_TRUE(areDistancesCorrect(adj,i,i,i,0)) << "Centroid calculates distances to antecessors of node " << i << " correctly";

	setUp(n);
	u = cn_build(n/2,0);
	EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
	for (int i = 0; i < n; i++)
		EXPECT_TRUE(areDistancesCorrect(adj,i,i,i,0)) << "Centroid calculates distances to antecessors of node " << i << " correctly";
}

TEST(CentroidLarge, Path) {
	setUp(10000);

	for (int i = 0; i < n; i++)
		adj[i].clear();
	for (int i = 1; i < n; i++) {
		adj[i].pb(i-1);
		adj[i-1].pb(i);
	}

	int u = cn_build(n-1,0);
	EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
	for (int i = 0; i < n; i++)
		EXPECT_TRUE(areDistancesCorrect(adj,i,i,i,0)) << "Centroid calculates distances to antecessors of node " << i << " correctly";
}

TEST(CentroidMedium, Random) {
	srand(42); rand(); rand();

	int ts = 5;

	while (ts--) {
		setUp(1000);

		for (int i = 0; i < n; i++)
			adj[i].clear();
		for (int i = 1; i < n; i++) {
			int j = rand()%i;
			adj[i].pb(j);
			adj[j].pb(i);
		}

		int u = cn_build(rand()%n,0);
		EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
		for (int i = 0; i < n; i++)
			EXPECT_TRUE(areDistancesCorrect(adj,i,i,i,0)) << "Centroid calculates distances to antecessors of node " << i << " correctly";
	}
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

		int u = cn_build(rand()%n,0);
		EXPECT_TRUE(isBalanced(cn_adj,u,u).first);
		for (int i = 0; i < n; i++)
			EXPECT_TRUE(areDistancesCorrect(adj,i,i,i,0)) << "Centroid calculates distances to antecessors of node " << i << " correctly";
	}
}
