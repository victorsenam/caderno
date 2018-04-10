#include <bits/stdc++.h>
using namespace std;

int main() {
    int p, a, b, c, d, n;
    scanf("%d %d %d %d %d %d", &p, &a, &b, &c, &d, &n);
    double mx = -1. / 0.;
    double ans = 0;
    for(int i = 1; i <= n; i++) {
        double x = p * (sin(a * i + b) + cos(c * i + d) + 2);
        mx = max(mx, x);
        ans = max(ans, mx - x);
    }
    printf("%.10f\n", ans);
}
