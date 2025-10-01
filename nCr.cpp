#include<bits/stdc++.h>
#define i64 long long
using namespace std;
const int mod = 998244353;
const int N = 2e5;
i64 fact[N + 1], invFact[N + 1];

i64 modPow(i64 a, i64 b) {
	i64 result = 1;
	while(b > 0) {
		if(b & 1) result = (result * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return result;
}

void precompute() {
	fact[0] = 1;
	for(int i = 1; i <= N; i++) fact[i] = (fact[i - 1] * i) % mod;

	invFact[N] = modPow(fact[N], mod - 2);
	for(int i = N - 1; i >= 0; i--) invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
}

i64 nCr(int n, int r) {
	if(r < 0 || r > n) return 0;
	return fact[n] * invFact[r] % mod * invFact[n - r] % mod;
}

void solve() {
	cout << nCr(5, 2) << "\n";
}

int main() {
	precompute();

	int t; cin >> t;
	while(t--) solve();
	return 0;
}
