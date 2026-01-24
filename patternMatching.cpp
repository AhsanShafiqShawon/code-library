#include<bits/stdc++.h>
#define i64 long long
using namespace std;

const int p1 = 137, mod1 = 127657753;
const int p2 = 277, mod2 = 987654319;
const int N = 1e6 + 5;
pair<int, int> pw[N], ipw[N], pref[N];

int bigMod(i64 a, i64 b, int mod) {
    int ans = 1;
    while(b) {
        if(b & 1) ans = 1LL * ans * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ans;
}

void prec() {
    pw[0] = {1, 1};
    for(int i = 1; i < N; i++) {
        pw[i].first = 1LL * pw[i - 1].first * p1 % mod1;
        pw[i].second = 1LL * pw[i - 1].second * p2 % mod2;
    }

    int invp1 = bigMod(p1, mod1 - 2, mod1);
    int invp2 = bigMod(p2, mod2 - 2, mod2);
    
    ipw[0] = {1, 1};
    for(int i = 1; i < N; i++) {
        ipw[i].first = 1LL * ipw[i - 1].first * invp1 % mod1;
        ipw[i].second = 1LL * ipw[i - 1].second * invp2 % mod2;
    }
}

pair<int, int> getHash(string s) {
    int n = s.size();
    
    pair<int, int> hash = {0, 0};
    for(int i = 0; i < n; i++) {
        hash.first += 1LL * s[i] * pw[i].first % mod1;
        hash.first %= mod1;

        hash.second += 1LL * s[i] * pw[i].second % mod2;
        hash.second %= mod2;
    }
    return hash;
}

void build(string s) {
    int n = s.size();
    
    for(int i = 0; i < n; i++) {
        pref[i].first = 1LL * s[i] * pw[i].first % mod1;
        if(i) pref[i].first = (pref[i].first + pref[i - 1].first) % mod1;

        pref[i].second = 1LL * s[i] * pw[i].second % mod2;
        if(i) pref[i].second = (pref[i].second + pref[i - 1].second) % mod2;
    }
}

pair<int, int> getSubStrHash(int i, int j) {
    assert(i <= j);
    pair<int, int> hash = {0, 0};
    
    hash.first = pref[j].first;
    if(i) hash.first = (hash.first - pref[i - 1].first + mod1) % mod1;
    hash.first = 1LL * hash.first * ipw[i].first % mod1;

    hash.second = pref[j].second;
    if(i) hash.second = (hash.second - pref[i - 1].second + mod2) % mod2;
    hash.second = 1LL * hash.second * ipw[i].second % mod2;

    return hash;
}

int main() {
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size();

    prec();
    build(s);

    auto tHash = getHash(t);
    int count = 0;
    for(int i = 0; i + m - 1 < n; i++) {
        if(getSubStrHash(i, i + m - 1) == tHash) count++;
    }
    cout << count << "\n";
    
    return 0;
}
