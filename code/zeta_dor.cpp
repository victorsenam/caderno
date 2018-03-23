//const int K = ;
//typedef ll num;

// overwrites b such that b[i] = sum (a[j]) such that (j | i) == i and popcount(j) = k
void tf(int k, num a[], num b[], int l, int r) {
	if(l == r) return (void) (b[l] = a[l] * (__builtin_popcount(l) == k));
	int m = (l + r) / 2;
	tf(k, a, b, l, m);
	tf(k, a, b, m + 1, r);
	for(int i = l; i <= m; i++)
		b[m + 1 + (i - l)] += b[i];
}

// Ranked mobius transform (transform above for all k)
void tf(int k, num a[], num b[K+1][1 << K]) {
	for(int i = 0; i <= k; i++)
		tf(i, a, b[i], 0, (1 << k) - 1);
}

// Convolutes two transforms. c[j][i] = sum(a[g][i] * b[k - g][i]) for 0 <= g <= j
void conv(int k, num a[K+1][1 << K], num b[K+1][1 << K], num c[K+1][1 << K]) {
	for(int j = 0; j <= k; j++)
		for(int i = 0; i < (1 << k); i++) {
			c[j][i] = 0;
			for(int g = 0; g <= j; g++)
				c[j][i] += a[g][i] * b[j - g][i];
		}
}

// Inverse of ranked mobius transform for k
void itf(num a[], int l, int r) {
	if(l == r) return;
	int m = (l + r) / 2;
	for(int i = l; i <= m; i++)
		a[m + 1 + (i - l)] -= a[i];
	itf(a, l, m);
	itf(a, m + 1, r);
}

// Inverse of ranked mobius transform for all k
void itf(int k, num a[K+1][1 << K], num b[]) {
	for(int j = 0; j <= k; j++) {
		itf(a[j], 0, (1 << k) - 1);
		for(int i = 0; i < (1 << k); i++)
			if(__builtin_popcount(i) == j)
				b[i] = a[j][i];
	}
}

// use when you want to calculate c[i] = sum (a[j] * b[k]) such that (j | k) == i and (j & k) = 0
// example use (if the size of a and b is (1 << k))
// tf(k, a, a_);
// tf(k, b, b_);
// conv(k, a_, b_, ans);
// itf(k, ans, c);
// the answer will now be stored in c
