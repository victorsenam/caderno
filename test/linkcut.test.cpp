#include <bits/stdc++.h>
using namespace std;
#include "gtest/gtest.h"

const int N = 1123456;
typedef int num;

#include "../code/linkcut.cpp"
inline int rnd(int l, int r) {
	double p = rand() / (double(RAND_MAX) + 1);
	return l + (r - l + 1) * p;
}

int check(int u, int pa=0) {
	if(!u) return 0;
	EXPECT_EQ(p[u], pa) << "wrong parent";
	int s = 1 + check(C[u][0], u) + check(C[u][1], u);
	EXPECT_EQ(sz[u], s) << "wrong size";
	return s;
}


TEST(LinkCut, Simple) {
	init();
	int a = new_node();
	int b = new_node();
	int c = new_node();
	EXPECT_NE(find(a), find(b));
	link(a, b);
	EXPECT_EQ(find(a), find(b));
	EXPECT_NE(find(a), find(c));
	EXPECT_EQ(find(a), find(b));
	cut(b);
	link(a, c);
	EXPECT_NE(find(a), find(b));
	EXPECT_NE(find(b), find(c));
	EXPECT_EQ(find(c), find(a));
}

int S[N];
int find_(int i) {
	if(S[S[i]] != S[i]) S[i] = find_(S[i]);
	return S[i];
}

TEST(LinkCut, UnionFind) {
	init();
	int n = 100000;
	for(int i = 1; i <= n; i++) S[i] = i, new_node();
	for(int i = 0; i < 400000; i++) {
		int a = rnd(1, n), b = rnd(1, n);
		if(rnd(0, 1000) == 0) {
			splay(a);
			check(a);
		}
		if(rnd(0, 2) == 0) {
			link(a, b);
			if((a = find_(a)) != (b = find_(b))) S[b] = a;
		} else
			EXPECT_EQ((find_(a) == find_(b)), (find(a) == find(b)));
	}
}

TEST(LinkCut, CutLine) {
	init();
	int n = 100000;
	for(int i = 1; i <= n; i++) new_node();
	for(int i = 1; i < n; i++) link(i, i + 1);
	for(int i = 0; i < n / 2; i++) {
		int g = rnd(1, n - 1);
		cut(g + 1);
		for(int k = 0; k < 10; k++) {
			int a = rnd(1, n), b = rnd(1, n);
			EXPECT_EQ((find(a) == find(b)), ((a <= g) == (b <= g)));
		}
		link(g, g + 1);
	}
}

int pe[N];
int low[N];

TEST(LinkCut, CutLine2) {
	init();
	int n = 100000;
	for(int i = 1; i <= n; i++) new_node(), pe[i] = i, low[i] = 1;
	for(int i = 1; i < n; i++) link(i, i + 1);
	random_shuffle(pe + 1, pe + n);
	for(int i = 1; i <= n - 1; i++) {
		int g = pe[i];
		cut(g + 1);
		for(int j = g + 1; j <= n && low[g] == low[j]; j++) low[j] = g + 1;
		for(int k = 0; k < 10; k++) {
			int a = rnd(1, n), b = rnd(1, n);
			EXPECT_EQ((find(a) == find(b)), (low[a] == low[b]));
		}
	}
}

TEST(LinkCut, CutLine3) {
	init();
	int n = 100000;
	for(int i = 1; i <= n; i++) new_node(), pe[i] = i, low[i] = 1;
	for(int i = 1; i < n; i++) link(i, i + 1);
	for(int g = 0; g < 1000; g++) {
		int a = rnd(1, n - 1), b = rnd(1, n - 1);
		swap(pe[a], pe[b]);
	}
	set<int> s;
	for(int i = 1; i <= n - 1; i++) {
		int g = pe[i];
		s.insert(g);
		cut(g + 1);
		for(int k = 0; k < 10; k++) {
			int a = rnd(1, n), b = rnd(1, n);
			EXPECT_EQ((find(a) == find(b)), (s.lower_bound(a) == s.lower_bound(b)));
		}
	}
}

vector<int> adj[N];
typedef pair<int, int> pii;
#define fst first
#define snd second

int seen[N], tempo = 0;
bool dfs(int a, int b) {
	if(seen[a] == tempo) return false;
	seen[a] = tempo;
	if(a == b) return true;
	for(int v : adj[a])
		if(dfs(v, b))
			return true;
	return false;
}

TEST(LinkCut, Brute) {
	init();
	int n = 3000;
	for(int i = 1; i <= n; i++) new_node();
	vector<pii> ed;
	for(int i = 0; i < 2 * n; i++) {
		if(ed.size() > 200 && rnd(0, 10) == 0) {
			int x = rnd(0, int(ed.size()) - 1);
			swap(ed[x], ed.back());
			cut(ed.back().snd);
			int u = ed.back().fst, v = ed.back().snd;
			adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, v));
			adj[v].erase(search_n(adj[v].begin(), adj[v].end(), 1, u));
			ed.pop_back();
		} else {
			int a = rnd(1, n), b = rnd(1, n);
			tempo++;
			if(dfs(a, b)) {
				EXPECT_EQ(find(a), find(b));
			} else {
				EXPECT_NE(find(a), find(b));
				if(b == find(b)) {
					link(a, b);
					ed.push_back(pii(a, b));
					adj[a].push_back(b);
					adj[b].push_back(a);
				}
			}
		}
	}
	for(int i = 1; i <= n; i++) adj[i].clear();
}
