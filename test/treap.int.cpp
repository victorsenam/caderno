#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int N = 1123456;
#include "gtest/gtest.h"
#include "../code/treap.cpp"

inline int rnd(int l, int r) {
	double p = rand() / (double(RAND_MAX) + 1);
	return l + (r - l + 1) * p;
}

inline int node(int val) {
	X[en] = val;
	return en++;
}

bool find(int &tree, int x) {
	int a, b, c;
	split_val(tree, x - 1, a, b);
	split_val(b, x, b, c);
	tree = merge(a, merge(b, c));
	return !!b;
}

int add(int &tree, int u) {
	int a, b;
	split_val(tree, X[u], a, b);
	return tree = merge(a, merge(u, b));
}
int remove(int &tree, int x) {
	int a, b, c;
	split_val(tree, x - 1, a, b);
	split_sz(b, 1, b, c);
	int del = 0;
	if(b && X[b] == x) b = 0, del = 1;
	tree = merge(a, merge(b, c));
	return del;
}

int dfs(int u, int mxY, int mnX, int mxX, bool bst) {
	if(u == 0) return 0;
	EXPECT_LT(Y[u], mxY) << "is not a treap";
	if(bst) EXPECT_GE(X[u], mnX) << "is not a BST";
	if(bst) EXPECT_LE(X[u], mxX) << "is not a BST";
	int size = 1;
	size += dfs(L[u], Y[u], mnX, X[u], bst);
	size += dfs(R[u], Y[u], X[u], mxX, bst);
	EXPECT_EQ(size, sz[u]) << "size is wrong";
	return size;
}

void check(int root, bool bst=true) {
	dfs(root, INT_MAX, INT_MIN, INT_MAX, bst);
}

TEST(TreapSimple, Simple) {
	init(10);
	for(int i = 1; i <= 10; i++)
		EXPECT_EQ(sz[i], 1) << "sizes should be 1";
	int root = 0;
	for(int i = 1; i <= 10; i++) {
		X[en] = i;
		root = merge(root, en++);
		check(root);
	}
	int a, b;
	split_val(root, 3, a, b);
	EXPECT_EQ(sz[a], 3) << "split not working";
	EXPECT_EQ(sz[b], 7) << "split not working";
	check(a); check(b);
	root = merge(a, b);
	EXPECT_EQ(sz[root], 10) << "merge not working";
	check(root);
}

TEST(TreapSimple, OutOfOrder) {
	init(10);
	int root = 0;
	root = add(root, node(1));
	root = add(root, node(0));
	check(root);
	root = add(root, node(2));
	check(root);
}

void to_vec(int u, vector<int> &v) {
	if(!u) return;
	to_vec(L[u], v);
	v.push_back(X[u]);
	to_vec(R[u], v);
}

// Testa se a treap ordena um vetor específico
void testSort(std::vector<int> &v) {
	init(v.size());
	int root = 0;
	for(int x : v)
		root = add(root, node(x));
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

TEST(TreapSorting, Simple) {
	vector<int> v = {10, 100, -3, 12, -100, 3, 2, 1};
	testSort(v);
}

TEST(TreapSorting, Repeated) {
	std::vector<int> v (10000, 10000);
	testSort(v);
}

TEST(TreapSorting, SortedReversed) {
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

TEST(TreapSorting, Small) { randomVecs(1000, 6, 15); }
TEST(TreapSorting, Medium) { randomVecs(1000, 100, 1000); }
TEST(TreapSorting, Large) { randomVecs(10, 10000, 100000); }

TEST(TreapRemove, Simpler) {
	init(10);
	int root = 0;
	EXPECT_FALSE(remove(root, 10)); check(root);
	add(root, node(12)); check(root);
	EXPECT_TRUE(remove(root, 12)); check(root);
	EXPECT_FALSE(remove(root, 12)); check(root);
	add(root, node(1)); check(root);
	add(root, node(2)); check(root);
	add(root, node(3)); check(root);
	add(root, node(4)); check(root);
	EXPECT_TRUE(remove(root, 2)); check(root);
	EXPECT_TRUE(remove(root, 1)); check(root);
}

TEST(TreapRemove, Simple) {
	init(100);
	int root = 0;
	for(int x : {1, 5, 7, 10})
		add(root, node(x));
	for(int x : {5, 10}) {
		EXPECT_TRUE(remove(root, x)) << "should contain";
		check(root);
	}
	for(int x : {1, 7, 1, 1})
		EXPECT_TRUE(find(root, x)) << "should find";
	for(int x : {10, -1, 5, 12})
		EXPECT_FALSE(find(root, x)) << "should not find";
}

TEST(TreapRemove, Odds) {
	init(100);
	int root = 0;
	for(int i = 0; i <= 100; i++)
		add(root, node(i));
	check(root);
	for(int i = 1; i <= 100; i += 2)
		EXPECT_TRUE(remove(root, i)) << "should remove";
	check(root);
	for(int i = 100; i >= 0; i--)
		EXPECT_EQ(find(root, i), (i % 2) == 0);
}

TEST(TreapRemove, Invalid) {
	init(50);
	int root = 0;
	for(int c = 'a'; c <= 'z'; c++)
		add(root, node(c));
	for(int c : {'a', 'z', 'c', 'a', 'a', '?'})
		remove(root, c);
	EXPECT_TRUE(remove(root, 'b'));
	EXPECT_FALSE(remove(root, '='));
	check(root);
	for(int c = 'a' - 12; c <= 'z' + 7; c++)
		EXPECT_EQ(find(root, c), c > 'c' && c < 'z');
}

TEST(TreapRemove, Repeated) {
	init(50000);
	int root = 0;
	int ct[3] = {0, 0, 0};
	for(int i = 0; i < 50000; i++) {
		int x = rnd(0, 2);
		ct[x]++;
		add(root, node(x));
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

TEST(TreapRemove, Breaks) {
	init(10);
	int root = 0;
	for(int x : {3, 5, 1, 4, 2, 6}) {
		add(root, node(x));
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
	init(1000000);
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
			add(root, node(v.back()));
			s.insert(v.back());
		}
		if((i % 100000) == 0) check(root);
	}
}

TEST(TreapRemove, Large) { doLarge(false); }
TEST(TreapRemove, LargeOrdered) { doLarge(true); }

TEST(TreapImplicit, Simple) {
	init(20);
	int root = 0;
	for(int x : {1, 2, 3, 4, 5, 4, 3, 2, 1})
		root = merge(root, node(x));
	check(root, false);
	int a, b, c;
	split_sz(root, 3, a, b);
	split_sz(b, 3, b, c);
	root = merge(b, merge(c, a));
	check(root, false);
	vector<int> ans, exp = {4, 5, 4, 3, 2, 1, 1, 2, 3};
	to_vec(root, ans);
	EXPECT_EQ(ans, exp) << "implicitness not working";
}

void swap_prefix(int &root, int sz) {
	int a, b;
	split_sz(root, sz, a, b);
	root = merge(b, a);
}

TEST(TreapImplicit, Medium) {
	init(1000); int root = 0;
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
		check(root, false);
	}
}
