#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 1e6+7;

int n, k;
ll a[N];

bool solve (ll d) {
	ll s = 0, m = n;
	for (int i = 0; m && i < 2*n*k - 1; i++) {
		if (a[i+1] - a[i] <= d) {
			m--;
			i++;
			s += 2*(k-1);
		} else if (!s) return 0;
		else s--;
	}
	return 1;
}

int main () {
	scanf("%d %d",&n, &k);

	for (int i = 0; i < 2*n*k; i++)
		scanf("%lld", &a[i]);
	sort(a, a+2*n*k);

	ll lo = 0, hi = 1e9+2;
	while (lo < hi) {
		ll md = (lo+hi)/2;
		if (solve(md)) hi = md;
		else lo = md+1;
	}

	printf("%lld\n", lo);
}
