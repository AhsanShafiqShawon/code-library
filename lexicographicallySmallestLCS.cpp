// LightOJ 1110
#include<bits/stdc++.h>
using namespace std;

string getLCS(int i, int j, int n, int m, string a, string b, map<pair<int, int>, string>& memo, vector<vector<int>>& dp) {
    if(i >= n or j >= m) return "";
    if(memo.count({i, j})) return memo[{i, j}];

    if(a[i] == b[j]) return memo[{i, j}] = a[i] + getLCS(i + 1, j + 1, n, m, a, b, memo, dp);
    if(dp[i + 1][j] > dp[i][j + 1]) return memo[{i, j}] = getLCS(i + 1, j, n, m, a, b, memo, dp);
    if(dp[i + 1][j] < dp[i][j + 1]) return memo[{i, j}] = getLCS(i, j + 1, n, m, a, b, memo, dp);

    string s1 = getLCS(i + 1, j, n, m, a, b, memo, dp);
    string s2 = getLCS(i, j + 1, n, m, a, b, memo, dp);

    return memo[{i, j}] = min(s1, s2);
}

void solve() {
    string a, b; cin >> a >> b;
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for(int i = n - 1; i >= 0; i--) {
        for(int j = m - 1; j >= 0; j--) {
            int ans = 0;
            if(a[i] == b[j]) ans = max(ans, 1 + dp[i + 1][j + 1]);
            else ans = max(ans, max(dp[i + 1][j], dp[i][j + 1]));

            dp[i][j] = ans;
        }
    }

    string lcs;
    int p = 0, q = 0;
    while(p < n and q < m) {
        if(a[p] == b[q]) {
            lcs.push_back(a[p]); p++; q++;
        } else if(dp[p + 1][q] > dp[p][q + 1]) {
            p++;
        } else if(dp[p + 1][q] < dp[p][q + 1]) {
            q++;
        } else {
            map<pair<int, int>, string> memo;
            string s1 = getLCS(p + 1, q, n, m, a, b, memo, dp);
            string s2 = getLCS(p, q + 1, n, m, a, b, memo, dp);

            if(s1 > s2) q++;
            else p++;
        }
    }

    if(lcs.empty()) cout << ":(\n";
    else cout << lcs << "\n";
}

int main() {
    int t; cin >> t;
    for(int i = 1; i <= t; i++) {
        cout << "Case " << i << ": ";
        solve();
    }
    return 0;
}
