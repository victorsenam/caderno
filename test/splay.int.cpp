#include <bits/stdc++.h>
using namespace std;
#include "gtest/gtest.h"

const int N = 1123456;
typedef int num;

#include "../code/splay.cpp"

int pe[N];

int check(int u, int pa=0, bool bst=true, int mnX=INT_MIN, int mxX=INT_MAX) {
	if(!u) return 0;
	EXPECT_EQ(p[u], pa) << "wrong parent";
	if(bst) EXPECT_LE(mnX, X[u]) << "not a bst";
	if(bst) EXPECT_GE(mxX, X[u]) << "not a bst";
	int s = 1 + check(C[u][0], u, bst, mnX, min(mxX, X[u])) + check(C[u][1], u, bst, max(mnX, X[u]), mxX);
	EXPECT_EQ(sz[u], s) << "wrong size";
	return s;
}

TEST(SplaySimple, Add) {
	init();
	int x = new_node(0);
	x = add(x, new_node(2));
	x = add(x, new_node(1));
	EXPECT_EQ(sz[x], 3);
	EXPECT_EQ(X[find_val(x, 0)], 0);
	EXPECT_EQ(X[find_val(x, 1)], 1);
	EXPECT_EQ(X[find_val(x, 2)], 2);
	EXPECT_NE(X[find_val(x, -1)], -1);
	EXPECT_NE(X[find_val(x, 3)], 3);
	x = find_val(x, 1);
	EXPECT_EQ(sz[x], 3);
	EXPECT_EQ(X[x], 1) << "must splay";
	check(x);
}

TEST(SplaySimple, Merge) {
	init();
	int x = new_node(0);
	x = merge(x, new_node(1));
	x = merge(x, new_node(2));
	EXPECT_EQ(sz[x], 3);
	EXPECT_EQ(X[find_val(x, 0)], 0);
	EXPECT_EQ(X[find_val(x, 1)], 1);
	EXPECT_EQ(X[find_val(x, 2)], 2);
	EXPECT_NE(X[find_val(x, -1)], -1);
	EXPECT_NE(X[find_val(x, 3)], 3);
	x = find_val(x, 1);
	EXPECT_EQ(sz[x], 3);
	EXPECT_EQ(X[x], 1) << "must splay";
	check(x);
}

TEST(SplaySimple, Finds) {
	int x = 0;
	for(int i = 0; i < 100; i++)
		x = add(x, new_node(i)), pe[i] = i;
	check(x);
	EXPECT_EQ(sz[x], 100);
	random_shuffle(pe, pe + 100);
	x = find_val(x, 92);
	check(x);
	x = find_sz(x, 93);
	for(int i_ = 0; i_ < 100; i_++) {
		int i = pe[i_];
		int a = find_val(x, i);
		x = find_val(a, rand() % 100); // find random eleemnt
		int b = find_sz(x, i);
		x = b;
		EXPECT_EQ(a, b);
		EXPECT_EQ(X[a], i);
	}
	check(x);
}

inline int rnd(int l, int r) {
	double p = rand() / (double(RAND_MAX) + 1);
	return l + (r - l + 1) * p;
}

inline int node(int val) {
	return new_node(val);
}

bool find(int &tree, int x) {
	tree = find_val(tree, x);
	return X[tree] == x;
}

int remove(int &tree, int x) {
	int u = find_val(tree, x);
	if(X[u] == x) {
		p[C[u][0]] = p[C[u][1]] = 0;
		tree = merge(C[u][0], C[u][1]);
		return true;
	} else tree = u;
	return false;
}

inline int _add(int &t, int u) {
	return t = add(t, u);
}

void to_vec(int u, vector<int> &v) {
	if(!u) return;
	to_vec(C[u][0], v);
	v.push_back(X[u]);
	to_vec(C[u][1], v);
}

// Testa se a splay ordena um vetor específico
void testSort(std::vector<int> &v) {
	init();
	int root = 0;
	for(int x : v)
		root = _add(root, node(x));
	check(root);
	std::sort(v.begin(), v.end()); // STL sort
	std::vector<int> ans;
	to_vec(root, ans);
	ASSERT_EQ(v, ans) << "Ordenacao incorreta";
}

// Testa T vetores aleatórios com tamanhos de l a r
void randomVecs(int T, int l, int r) {
	for(int t = 0; t < T; t++) {
		int n = rnd(l, r);
		std::vector<int> v;
		for(int i = 0; i < n; i++)
			v.push_back(rand());
		testSort(v);
	}
}

TEST(SplaySorting, Simple) {
	vector<int> v = {10, 100, -3, 12, -100, 3, 2, 1};
	testSort(v);
}

TEST(SplaySorting, Repeated) {
	std::vector<int> v (10000, 10000);
	testSort(v);
}

TEST(SplaySorting, SortedReversed) {
	for(int t = 0; t < 10; t++) {
		std::vector<int> v;
		for(int i = 0; i < 30000; i++)
			v.push_back(rand() % 30000);
		std::sort(v.begin(), v.end());
		if(t % 2)
			std::reverse(v.begin(), v.end());

		testSort(v);
	}
}

TEST(SplaySorting, Small) { randomVecs(1000, 6, 15); }
TEST(SplaySorting, Medium) { randomVecs(1000, 100, 1000); }
TEST(SplaySorting, Large) { randomVecs(10, 10000, 100000); }

TEST(SplayRemove, Simpler) {
	init();
	int root = 0;
	EXPECT_FALSE(remove(root, 10)); check(root);
	_add(root, node(12)); check(root);
	EXPECT_TRUE(remove(root, 12)); check(root);
	EXPECT_FALSE(remove(root, 12)); check(root);
	_add(root, node(1)); check(root);
	_add(root, node(2)); check(root);
	_add(root, node(3)); check(root);
	_add(root, node(4)); check(root);
	EXPECT_TRUE(remove(root, 2)); check(root);
	EXPECT_TRUE(remove(root, 1)); check(root);
}

TEST(SplayRemove, Simple) {
	init();
	int root = 0;
	for(int x : {1, 5, 7, 10})
		_add(root, node(x));
	for(int x : {5, 10}) {
		EXPECT_TRUE(remove(root, x)) << "should contain";
		check(root);
	}
	for(int x : {1, 7, 1, 1})
		EXPECT_TRUE(find(root, x)) << "should find";
	for(int x : {10, -1, 5, 12})
		EXPECT_FALSE(find(root, x)) << "should not find";
}

TEST(SplayRemove, Odds) {
	init();
	int root = 0;
	for(int i = 0; i <= 100; i++)
		_add(root, node(i));
	check(root);
	for(int i = 1; i <= 100; i += 2)
		EXPECT_TRUE(remove(root, i)) << "should remove";
	check(root);
	for(int i = 100; i >= 0; i--)
		EXPECT_EQ(find(root, i), (i % 2) == 0);
}

TEST(SplayRemove, Invalid) {
	init();
	int root = 0;
	for(int c = 'a'; c <= 'z'; c++)
		_add(root, node(c));
	for(int c : {'a', 'z', 'c', 'a', 'a', '?'})
		remove(root, c);
	EXPECT_TRUE(remove(root, 'b'));
	EXPECT_FALSE(remove(root, '='));
	check(root);
	for(int c = 'a' - 12; c <= 'z' + 7; c++)
		EXPECT_EQ(find(root, c), c > 'c' && c < 'z');
}

TEST(SplayRemove, Repeated) {
	init();
	int root = 0;
	int ct[3] = {0, 0, 0};
	for(int i = 0; i < 50000; i++) {
		int x = rnd(0, 2);
		ct[x]++;
		_add(root, node(x));
	}
	int p[3] = {0, 1, 2};
	while(ct[0] + ct[1] + ct[2] > 0) {
		std::random_shuffle(p, p + 3);
		int i = 0;
		while(ct[p[i]] == 0) i++;
		int x = p[i];
		ct[x]--;
		ASSERT_TRUE(remove(root, x));
		if(((ct[0] + ct[1] + ct[2]) % 2500) == 0) check(root);
	}
}

TEST(SplayRemove, Breaks) {
	init();
	int root = 0;
	for(int x : {3, 5, 1, 4, 2, 6}) {
		_add(root, node(x));
		check(root);
	}
	for(int x : {4, 5, 6}) {
		EXPECT_TRUE(remove(root, x));
		check(root);
	}
}

void doLarge(bool isOrdered) {
	std::vector<int> v;
	std::multiset<int> s;
	init();
	int root = 0;
	for(int i = 0; i <= 1000000; i++) {
		int p = rnd(1, 100);
		if(p <= 30 && v.size() > 1) {
			int j = rnd(0, v.size() - 1);
			if(isOrdered) j = v.size() - 1;
			std::swap(v[j], v.back());
			EXPECT_TRUE(remove(root, v.back()));
			s.erase(s.find(v.back()));
			v.pop_back();
		} else if(p >= 85 && v.size() > 0) {
			int j = rnd(0, v.size() - 1);
			EXPECT_TRUE(find(root, v[j]));
			int x = rand();
			EXPECT_EQ(find(root, x), s.find(x) != s.end());
		} else {
			if(isOrdered) v.push_back(i);
			else v.push_back(rand() * rand() + rand());
			_add(root, node(v.back()));
			s.insert(v.back());
		}
		if((i % 100000) == 0) check(root);
	}
}

TEST(SplayRemove, Large) { doLarge(false); }
TEST(SplayRemove, LargeOrdered) { doLarge(true); }

void split_sz(int u, int s, int &l, int &r) {
	if(s == sz[u]) { l = u; r = 0; return; }
	u = find_sz(u, s - 1);
	l = u;
	r = C[u][1];
	p[C[u][1]] = 0;
	C[u][1] = 0;
	calc(l);
}

TEST(SplayImplicit, Simple) {
	init();
	int root = 0;
	for(int x : {1, 2, 3, 4, 5, 4, 3, 2, 1})
		root = merge(root, node(x));
	check(root, 0,  false);
	int a, b, c;
	split_sz(root, 3, a, b);
	split_sz(b, 3, b, c);
	root = merge(b, merge(c, a));
	check(root, 0, false);
	vector<int> ans, exp = {4, 5, 4, 3, 2, 1, 1, 2, 3};
	to_vec(root, ans);
	EXPECT_EQ(ans, exp) << "implicitness not working";
}

void swap_prefix(int &root, int sz) {
	int a, b;
	split_sz(root, sz, a, b);
	root = merge(b, a);
}

TEST(SplayImplicit, Medium) {
	init(); int root = 0;
	deque<int> v;
	for(int i = 0; i < 1000; i++) {
		root = merge(root, node(i));
		v.push_back(i);
	}
	for(int i = 0; i < 1000; i++) {
		int sz = rnd(1, 999);
		swap_prefix(root, sz);
		for(int j = 0; j < sz; j++)
			v.push_back(v.front()), v.pop_front();
		vector<int> ans, exp(v.begin(), v.end());
		to_vec(root, ans);
		EXPECT_EQ(ans, exp);
		check(root, 0, false);
	}
}
