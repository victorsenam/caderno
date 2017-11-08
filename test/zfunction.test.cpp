#include <bits/stdc++.h>
using namespace std;
#include "gtest/gtest.h"
const int N = 512345;
#include "../code/zfunction.cpp"

inline void cp(string x) {
	int i = 0;
	for(char c : x) s[i++] = c;
}

void test_brut(string x) {
	cp(x);
	Z(x.size());
	for(int i = 1; i < int(x.size()); i++) {
		int Z = 0;
		while(i + Z < int(x.size()) && s[i + Z] == s[Z]) Z++;
		EXPECT_EQ(Z, z[i]);
	}
}

TEST(Simple, Small) {
	for(string x : {"", "a", "aaa", "abc", "abacaba", "hohoho", "hoheho"})
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
}

TEST(Simple, Big) {
	for(int i = 0; i < N; i++) s[i] = 'z';
	Z(N);
	for(int i = 1; i < N; i++) EXPECT_EQ(z[i], N - i);
	for(int g = 0; g < 20; g++) {
		s[rand() % N] = 'a' + g;
		Z(N);
		int mx = 0;
		for(; mx < N && s[mx] == 'z'; mx++);
		int cur = 0;
		for(int i = N - 1; i > 0; i--) {
			cur++;
			if(s[i] != 'z') cur = 0;
			EXPECT_EQ(z[i], min(cur, mx)) << "for " << i ;
		}
	}
}

