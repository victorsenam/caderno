//const int N = ;

double a[N][N];
double ans[N];

// sum(a[i][j] * x_j) = a[i][n] para 0 <= i < n
// guarda a resposta em ans e retorna o determinante de a
double solve(int n) {
	double det = 1;
	for(int i = 0; i < n; i++) {
		int mx = i;
		for(int j = i + 1; j < n; j++)
			if(abs(a[j][i]) > abs(a[mx][i]))
				mx = j;
		if(i != mx) {
			swap_ranges(a[i], a[i] + n + 1, a[mx]);
			det = -det;
		}
		if(abs(a[i][i]) < 1e-6) /* matriz singular */;
		det *= a[i][i];
		for(int j = i + 1; j < n; j++) {
			for(int k = i + 1; k <= n; k++)
				a[j][k] -= (a[j][i] / a[i][i]) * a[i][k];
			a[j][i] = 0;
		}
	}
	for(int i = n - 1; i >= 0; i--) {
		ans[i] = a[i][n];
		for(int j = i + 1; j < n; j++)
			ans[i] -= a[i][j] * ans[j];
		ans[i] /= a[i][i];
	}
	return det;
}
