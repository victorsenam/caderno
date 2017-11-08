//const int N = ;

char s[N];
char t[2 * N];
int M[2 * N];
// Maximum odd palindrome centered on i: [i - M[2 * i] / 2, i + M[2 * i] / 2]
// Maximum even palindrome centered on i and i+1: [i + 1 - (M[2 * i + 1] + 1) / 2, i + (M[2 * i + 1] + 1) / 2] (if M[2 * i + 1] != 0)

void manacher(int n) {
	for(int i = 0; i < n; i++) t[2 * i] = s[i];
	for(int i = 0; i < n - 1; i ++) t[2 * i + 1] = 1; // cant be on s
	n = 2 * n - 1;

	int m = -1;
	for(int i = 0; i < n; i++) {
		M[i] = 0;
		if(m != -1 && m + M[m] >= i)
			M[i] = min(m + M[m] - i, M[2 * m - i]);
		while(i + M[i] + 1 < n && i - M[i] - 1 >= 0 && t[i + M[i] + 1] == t[i - M[i] - 1])
			M[i]++;
		if(m == -1 || i + M[i] > m + M[m])
			m = i;
	}
}
