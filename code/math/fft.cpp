typedef complex<double> cpx; const double pi = acos(-1.0);
// DFT if type = 1, IDFT if type = -1
// If you are multiplying, remember to let EACH vector with n >= sum of degrees of both polys
// n is required to be a power of 2
void FFT(cpx v[], cpx ans[], int n, int type, int p[]) { // p[n]
	assert(!(n & (n - 1))); int i, sz, o; p[0] = 0;
	for(i = 1; i < n; i++) p[i] = (p[i >> 1] >> 1) | ((i & 1)? (n >> 1) : 0); // repetition can be avoided
	for(i = 0; i < n; i++) ans[i] = v[p[i]];
	for(sz = 1; sz < n; sz <<= 1) {
		const cpx wn(cos(type * pi / sz), sin(type * pi / sz));
		for(o = 0; o < n; o += (sz << 1)) {
			cpx w = 1;
			for(i = 0; i < sz; i++) {
				const cpx u = ans[o + i], t = w * ans[o + sz + i];
				ans[o + i] = u + t;
				ans[o + i + sz] = u - t;
				w *= wn;
			}
		}
	}
	if(type == -1) for(i = 0; i < n; i++) ans[i] /= n;
}
