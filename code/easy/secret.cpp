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

char adj[256][256];
char seen[256];

void go(char p, char u) {
    if(seen[u] == p) return;
    seen[u] = p;
    adj[p][u] = 1;
    for(int v = 'a'; v <= 'z'; v++)
        if(adj[u][v])
            go(p, v);
}

char s[1123], t[1123];

int main() {
    int i, m, n, j;
    scanf("%d %d", &m, &n);
    for(i = 0; i < m; i++) {
        char a, b;
        scanf(" %c %c", &a, &b);
        adj[a][b] = 1;
    }
    for(i = 'a'; i <= 'z'; i++)
        go(i, i);
    for(i =0 ; i < n; i++) {
        scanf("%s %s", s, t);
        if(strlen(s) != strlen(t)) { puts("no"); continue; }
        for(j = 0; s[j]; j++)
            if(!adj[s[j]][t[j]])
                break;
        if(s[j]) puts("no");
        else puts("yes");
    }
}
