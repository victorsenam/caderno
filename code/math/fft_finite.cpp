#include <bits/stdc++.h>
//#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// const int N = ;
// typedef long long num;
int pr[N];
num w[N];

inline num s_mod (ll x, ll p) {
	if (x >= p) return x-p;
	else if (x < 0) return x += p;
	return x;
}

num fexp (ll x, int e, num p) {
	ll r = 1;
	while (e) {
		if (e&1) r = (r*x)%p;
		x = (x*x)%p;
		e >>= 1;
	}
	return r;
}

void rou (int n, int p) {
	w[0] = 1;
	bool ok = 0;
	for (num i = 2; !ok && i < p; i++) {
		ok = 1;
		for (ll j = 2; ok && j*j <= p-1; j++)
			if ((p-1)%j == 0)
				ok = !(fexp(i,j,p) == 1 || fexp(i,(p-1)/j,p) == 1);
		if (ok)
			w[1] = fexp(i,(p-1)/n,p);
	}
	assert(ok);
	for (int i = 2; i <= n; i++)
		w[i] = (ll(w[i-1])*w[1])%p;
}

void fft_finite (num v[], num ans[], int n, int type, num p) {
	assert(!(n & (n-1)));
	rou(n,p); ll invn = fexp(n,p-2,p); // pode ser aproveitado de chamadas diferentes
	if (type == -1) reverse(w, w+n+1);

	pr[0] = 0;
	for (int i = 1; i < n; i++) pr[i] = ((pr[i>>1] >> 1) | ((i&1)?(n>>1):0));
	for (int i = 0; i < n; i++) ans[i] = v[pr[i]];
	for (int sz = 1; sz < n; sz <<= 1) {
		for (int o = 0; o < n; o += (sz<<1)) {
			for (int i = 0; i < sz; i++) {
				const num u = ans[o+i], t = (w[(n/sz/2)*i]*ans[o+sz+i])%p;
				ans[o+i] = s_mod(u+t,p);
				ans[o+i+sz] = s_mod(u-t,p);
			}
		}
	}

	if(type == -1) for(int i = 0; i < n; i++) ans[i] = (ans[i]*invn)%p;
}

