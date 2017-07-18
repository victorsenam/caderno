#include <bits/stdc++.h>
using namespace std;
#define debug if (1)

typedef long long ll;

// typedef ll num;
// const num eps = 0;
// const num inf = LLONG_MAX;

// const int N = ;
// const int M = ;

// TESTS TODO
struct dinic {
    // O(MN^2)
    // BipMatch: O(MN^(1/2))
    // UnitCap: O(min{MV^(2/3),M^(3/2)}
    int hd[N], nx[M], to[M], ht[M], es;
    num fl[M], cp[M];
    int n, src, snk;
    int ds[N], sn[N], tr;
    int qi, qf, qu[N];

    void init ()
    { es = 2; memset(hd, 0, sizeof hd); }

    void connect (int i, int j, num cap) {
        to[es] = j; nx[es] = hd[i]; cp[es] = cap; fl[es] = 0; hd[i] = es++;
        to[es] = i; nx[es] = hd[j]; cp[es] = fl[es] = 0; hd[j] = es++;
    }

    bool bfs () {
        tr += 2;
        qi = qf = 0;

        qu[qf++] = snk;
        ds[snk] = 0;

        while (qi < qf) {
            int u = qu[qi++];

            if (sn[u] > tr)
                continue;
            sn[u] = tr+1;

            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (cp[ed^1] - fl[ed^1] <= eps)
                    continue;
                int v = to[ed];

                if (sn[v] >= tr && ds[v] <= ds[u] + 1)
                    continue;
                sn[v] = tr;
                ds[v] = ds[u] + 1;
                qu[qf++] = v;
            }
        }

        return (sn[src] > tr);
    }

    num dfs (int u, num flw) {
        if (u == snk || flw <= eps)
            return flw;

        for (int & ed = ht[u]; ed; ed = nx[ed]) {
            int v = to[ed];
            if (cp[ed] - fl[ed] <= eps || sn[v] < tr || ds[v] + 1 != ds[u])
                continue;
            num ret = dfs(v, min(flw, cp[ed] - fl[ed]));
            if (ret > eps) {
                fl[ed] += ret;
                fl[ed^1] -= ret;
                return ret;
            }
        }

        return 0;
    }

    num maxflow () {
        num res = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++)
                ht[i] = hd[i];
            num val = 0;
            do {
                res += val;
                val = dfs(src, inf);
            } while (val > eps);
        }
        return res;
    }
};
