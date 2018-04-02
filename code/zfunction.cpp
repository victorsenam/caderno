void Z(char s[], int n, int z[]) { // z[i] = |lcp(s,s[i..n])|
	for(int i = 1, m = -1; i < n; i++) {
		z[i] = (m != -1 && m + z[m] >= i)?min(m + z[m] - i, z[i - m]):0;
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if (m == -1 || i + z[i] > m + z[m]) m = i;
	}
}
