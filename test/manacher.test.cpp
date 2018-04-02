#include <bits/stdc++.h>
using namespace std;
#include "gtest/gtest.h"
const int N = 512345;
char s[N], t[2*N]; int M[2*N];
#include "../code/manacher.cpp"

inline void cp(string x) {
	int i = 0;
	for(char c : x) s[i++] = c;
}

void test_brut(string x) {
	cp(x);
	manacher(s,x.size(),t,M);
	for(int i = 0; i < int(x.size()); i++) {
		int M = 0;
		while(i + M + 1 < int(x.size()) && i - M - 1 >= 0 && x[i + M + 1] == x[i - M - 1]) M++;
		EXPECT_EQ(M, ::M[2 * i] / 2) << "error on \"" << x << "\" pos " << i << " even palindrome";
		if(i < int(x.size()) - 1 && x[i] == x[i + 1]) {
			M = 0;
			while(i - M >= 0 && i + M + 1 < int(x.size()) && x[i - M] == x[i + M + 1])
				M++;
			EXPECT_EQ(i - M + 1, i + 1 - (::M[2 * i + 1] + 1) / 2);
			EXPECT_EQ(i + M, i + (::M[2 * i + 1] + 1) / 2);
		}
	}
}

TEST(Simple, Small) {
	for(string x : {"", "a", "aaa", "abc", "abacaba", "hohoho", "hoheho", "abba", "babaca"})
		test_brut(x);
	for(string x : {"aaab", "abcd", "aaaaaaabb", "abcabcabc"}) {
		do test_brut(x); while(next_permutation(x.begin(), x.end()));
	}
	string s;
	for(int i = 0; i < 1000; i++) s.push_back('d');
	test_brut(s);
	for(int i = 0; i < 10; i++) s.push_back('g');
	for(int i = 0; i < 5; i++) {
		random_shuffle(s.begin(), s.end());
		test_brut(s);
	}
}

TEST(Simple, Random) {
	for(int dif : {2, 3, 4, 5, 10, 15, 20, 26}) {
		const int n = 10000;
		for(int t = 0; t < 10; t++) {
			string s;
			for(int i = 0; i < n; i++)
				s.push_back('a' + (rand() % dif));
			test_brut(s);
		}
	}
	string s;
	const int n = 2000;
	for(int i = 0; i < n; i++)
		s.push_back('a' + (rand() % 2));
	for(int i = 0; i < 100; i++) {
		int l = rand() % n, r = rand() % n; if(l > r) swap(l, r);
		string x = s.substr(l, r - l + 1);
		int p = rand() % (n - (r - l));
		for(int j = 0; j < r - l + 1; j++)
			s[j + p] = x[x.size() - 1 - j];
	}
}

TEST(Simple, Big) {
	string s;
	for(int i = 0; i < N; i++) s.push_back('z');
	cp(s); manacher(::s,N,t,M);
	for(int i = 0; i < N; i++) EXPECT_EQ(M[2 * i] / 2, min(i, N - 1 - i));
	for(int g = 0; g < N; g++) {
		s[rand() % N] = 'a' + (g % 20);
		if(g == N / 100 || g == N / 30 || g == N / 10 || g == N / 2 || g == N)
			test_brut(s);
	}
}

