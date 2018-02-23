//typedef long double dbl;
const dbl eps = 1e-6;
//const int N = , M = ;

struct simplex {
	int X[N], Y[M];
	dbl A[M][N], b[M], c[N];
	dbl ans;
	int n, m;
	dbl sol[N];

	void pivot(int x,int y){
		swap(X[y], Y[x]);
		b[x] /= A[x][y];
		for(int i = 0; i < n; i++)
			if(i != y)
				A[x][i] /= A[x][y];
		A[x][y] = 1. / A[x][y];
		for(int i = 0; i < m; i++)
			if(i != x && abs(A[i][y]) > eps) {
				b[i] -= A[i][y] * b[x];
				for(int j = 0; j < n; j++)
					if(j != y)
						A[i][j] -= A[i][y] * A[x][j];
				A[i][y] = -A[i][y] * A[x][y];
			}
		ans += c[y] * b[x];
		for(int i = 0; i < n; i++)
			if(i != y)
				c[i] -= c[y] * A[x][i];
		c[y] = -c[y] * A[x][y];
	}

	/* maximiza sum(x[i] * c[i])
	 * sujeito a sum(a[i][j] * x[j]) <= b[i] para 0 <= i < m
	 * (n variáveis, m restrições)
	 * guarda a resposta em ans e retorna o valor dela
	 */
	dbl solve(int n, int m) {
		this->n = n; this->m = m;
		ans = 0.;
		for(int i = 0; i < n; i++) X[i] = i;
		for(int i = 0; i < m; i++) Y[i] = i + n;
		while(true) {
			int x = min_element(b, b + m) - b;
			if(b[x] >= -eps)
				break;
			int y = find_if(A[x], A[x] + n, [](dbl d) { return d < -eps; }) - A[x];
			if(y == n) throw 1; // no solution
			pivot(x, y);
		}
		while(true) {
			int y = max_element(c, c + n) - c;
			if(c[y] <= eps) break;
			int x = -1;
			dbl mn = 1. / 0.;
			for(int i = 0; i < m; i++)
				if(A[i][y] > eps && b[i] / A[i][y] < mn)
					mn = b[i] / A[i][y], x = i;
			if(x == -1) throw 2; // unbounded
			pivot(x, y);
		}
		memset(sol, 0, sizeof(dbl) * n);
		for(int i = 0; i < m; i++)
			if(Y[i] < n)
				sol[Y[i]] = b[i];
		return ans;
	}
};
