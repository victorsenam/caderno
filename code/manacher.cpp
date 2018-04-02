// max odd pali cent on i: s[i - M[2 * i] / 2..i + M[2 * i] / 2]
// max even pali cent on [i,i+1]: s[i + 1 - (M[2*i+1] + 1) / 2..i + (M[2*i+1] + 1) / 2] (if M[2*i+1] != 0)
void manacher(char s[], int n, char t[], int M[]) { // t and M should have size 2*n
	for(int i = 0; i < n; i++) t[2 * i] = s[i];
	for(int i = 0; i < n - 1; i++) t[2 * i + 1] = 1; // XXX s should not contain 1
	n = 2 * n - 1;
	for(int i = 0, m = -1; i < n; i++) {
		M[i] = 0;
		if (m != -1 && m + M[m] >= i) M[i] = min(m + M[m] - i, M[2 * m - i]);
		for (; i + M[i] + 1 < n && i - M[i] - 1 >= 0 && t[i + M[i] + 1] == t[i - M[i] - 1]; M[i]++);
		if (m == -1 || i + M[i] > m + M[m]) m = i;
	}
}
