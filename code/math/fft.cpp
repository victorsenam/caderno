#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

typedef complex<double> num;
const double pi = acos(-1.0);
//const int N = ;
int p[N];

// DFT if type = 1, IDFT if type = -1
// If you are multiplying, remember to let EACH vector with n >= sum of degrees of both polys
// n is required to be a power of 2
void FFT(num v[], num ans[], int n, int type) {
	assert(!(n & (n - 1)));
	int i, sz, o;
	p[0] = 0;
	for(i = 1; i < n; i++) p[i] = (p[i >> 1] >> 1) | ((i & 1)? (n >> 1) : 0);
	for(i = 0; i < n; i++) ans[i] = v[p[i]];
	for(sz = 1; sz < n; sz <<= 1) {
		const num wn(cos(type * pi / sz), sin(type * pi / sz));
		for(o = 0; o < n; o += (sz << 1)) {
			num w = 1;
			for(i = 0; i < sz; i++) {
				const num u = ans[o + i], t = w * ans[o + sz + i];
				ans[o + i] = u + t;
				ans[o + i + sz] = u - t;
				w *= wn;
			}
		}
	}
	if(type == -1) for(i = 0; i < n; i++) ans[i] /= n;
}
