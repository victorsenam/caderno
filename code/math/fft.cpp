#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const double pi = acos(-1.0);
typedef complex<double> cpx;

// XXX assumes v.size() is power of 2
// if inv is true, runs inverse DFT
void fft (vector<cpx> & ans, vector<cpx> & a, vector<int> & p, bool inv) {
    int n = a.size();
    assert(!(n&(n-1)));
    assert(n == int(ans.size()));
    assert(n == int(p.size()));

    for (int i = 0; i < n; i++)
        ans[i] = a[p[i]];

    for (int sz = 1; sz < n; sz <<= 1) {
        const cpx root(cos(pi / sz), sin((1. - inv - inv) * pi / sz));
        for (int j = 0; j < n; j += (sz << 1)) {
            cpx w = 1;
            for (int i = 0; i < sz; i++) {
                const cpx t = w * ans[i + j + sz];
                ans[i + j + sz] = ans[i + j] - t;
                ans[i + j] += t;
                w *= root;
            }
        }
    }

    if (inv)
        for (int i = 0; i < n; i++)
            ans[i] /= n;
}

// XXX tested precision: 9 decimal digits (1e-9 when values vary on [-10,10])
void product (vector<cpx> & ans, vector<cpx> & a, vector<cpx> & b, bool padded = 0) {
    int n = max(a.size(), b.size());
    
    if (!padded) {
        while (n&(n-1)) n += (n&-n); // geq power of 2
        n += n;

        a.resize(n,0);
        b.resize(n,0);
        ans.resize(n,0);

    }

    vector<int> p(n);
    p[0] = 0;
    for (int i = 1; i < n; i++)
        p[i] = (p[i >> 1] >> 1) | ((i&1) ? (n >> 1) : 0);

    fft(ans, a, p, 0);
    fft(a, b, p, 0);
    for (int i = 0; i < n; i++)
        a[i] *= ans[i];
    fft(ans, a, p, 1);
}
