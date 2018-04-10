#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 1123;
int d[N], s[N];

int main() {
    int n, t, i;
    scanf("%d %d", &n, &t);
    long double l = -2e7, r = 1502;
    for(i = 0; i < n; i++) scanf("%d %d", &d[i], &s[i]);
    for(int x = 0; x < 200; x++) {
        long double c = (l + r) / 2;
        long double tot = 0;
        for(i = 0; i < n; i++) {
            long double ss = s[i] - c;
            if(ss <= 0) break;
            tot += d[i] / ss;
        }
        if(tot >= t || i < n) r = c;
        else l = c;
    }
    printf("%.10f\n", -double(l));

}
