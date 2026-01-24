#include<bits/stdc++.h>
using namespace std;

const int p1 = 137, mod1 = 1e9 + 7;
const int p2 = 277, mod2 = 1e9 + 9;
const int N = 1e5 + 5;
int pw1[N], pw2[N];

void prec() {
    pw1[0] = 1;
    for(int i = 1; i < N; i++) pw1[i] = 1LL * pw1[i - 1] * p1 % mod1;

    pw2[0] = 1;
    for(int i = 1; i < N; i++) pw2[i] = 1LL * pw2[i - 1] * p2 % mod2;
}

pair<int, int> getHash(string s) {
    int n = s.size();
    
    int hash1 = 0;
    for(int i = 0; i < n; i++) {
        hash1 += 1LL * s[i] * pw1[i] % mod1;
        hash1 %= mod1;
    }

    int hash2 = 0;
    for(int i = 0; i < n; i++) {
        hash2 += 1LL * s[i] * pw2[i] % mod2;
        hash2 %= mod2;
    }

    return {hash1, hash2};
}

int main() {
    prec();

    string s, t; cin >> s >> t;
    cout << boolalpha << (getHash(s) == getHash(t)) << "\n";
    return 0;
}
