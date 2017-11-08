//const int N = ;

char s[N];
int z[N]; // z[i] = |lcp(s, s[i...])|

void Z(int n) {
	int m = -1;
	for(int i = 1; i < n; i++) {
		z[i] = 0;
		if(m != -1 && m + z[m] >= i)
			z[i] = min(m + z[m] - i, z[i - m]);
		while(i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if(m == -1 || i + z[i] > m + z[m])
			m = i;
	}
}
