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

const int N = 112345;
int L[N], R[N], v[N];
int en = 1;

int add(int r, int x) {
    if(r == 0) {
        r = en++;
        v[r] = x;
        return r;
    }
    if(x < v[r])
        L[r] = add(L[r], x);
    else
        R[r] = add(R[r], x);
    return r;
}

string get_str(int r) {
    if(r == 0) return "";
    return "(" + get_str(L[r]) + "," + get_str(R[r]) + ")";
}

string s[112345];

int main() {
    int n, k, i, j, x;
    scanf("%d %d", &n, &k);
    for(i = 0; i < n; i++) {
        int root = 0;
        for(j = 0; j < k; j++) {
            scanf("%d", &x);
            root = add(root, x);
        }
        s[i] = get_str(root);
    }
    sort(s, s + n);
    printf("%d\n", int(unique(s, s + n) - s));
}
