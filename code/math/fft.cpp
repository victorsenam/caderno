#include "../header.cpp"

const double pi = acos(-1.0);
typedef complex<double> cpx;


// XXX assumes v.size() is power of 2
// if inv is true, runs inverse DFT
vector<cpx> fft (vector<cpx> & a, bool inv) {
    int n = a.size();
    assert(!(n&(n-1)));

    vector<int> p(n,0);
    vector<cpx> ans(n);

    for (int i = 1; i < n; i++)
        p[i] = (p[i >> 1] >> 1) | ((i&1) ? (n >> 1) : 0);
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

    return ans;
}

// XXX tested precision: 9 decimal digits (1e-9 when values vary on [-10,10])
vector<cpx> product (vector<cpx> a, vector<cpx> b) {
    int n = max(a.size(), b.size());
    
    while (n&(n-1)) n += (n&-n); // geq power of 2
    n += n;

    a.resize(n,0);
    b.resize(n,0);

    a = dft(a,0);
    b = dft(b,0);
    for (int i = 0; i < n; i++)
        a[i] *= b[i];
    return dft(a,1);
}
