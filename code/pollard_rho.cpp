llu rho(llu n) {
	llu d, c = rand() % n, x = rand() % n, xx = x;
	if (n % 2 == 0)
		return 2;
	do {
		x = (mul_mod(x, x, n) + c) % n;
		xx = (mul_mod(xx, xx, n) + c) % n;
		xx = (mul_mod(xx, xx, n) + c) % n;
		d = gcd(val_abs(x - xx), n);
	} while (d == 1);
	return d;
}
map <llu,int> F;
void factor(llu n) {
	if (n == 1)
		return;
	if (is_probably_prime(n)) {
		F[n]++;
		return;
	}
	llu d = rho(n);
	factor(d);
	factor(n/d);
}
