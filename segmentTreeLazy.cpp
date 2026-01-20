#include<bits/stdc++.h>
#define i64 long long
using namespace std;
const int N = 1e5 + 5;
i64 tree[4 * N], lazy[4 * N];

void push(int node, int l, int r) {
    if(lazy[node] == 0) return;

    tree[node] += lazy[node] * (r - l + 1);
    if(l != r) {
        lazy[2 * node + 1] += lazy[node];
        lazy[2 * node + 2] += lazy[node];
    }
    lazy[node] = 0;
}

void update(int node, int l, int r, int b, int e, int value) {
    push(node, l, r);
    if(e < l or r < b) return;
    if(b <= l and r <= e) {
        lazy[node] += value;
        push(node, l, r);
        return;
    }

    int mid = l + (r - l) / 2;
    update(2 * node + 1, l, mid, b, e, value);
    update(2 * node + 2, mid + 1, r, b, e, value);
    
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

void query(int node, int l, int r, int index, i64& ans) {
    push(node, l, r);

    if(index < l or index > r) return;
    if(l == index and r == index) {
        ans = tree[node]; return;
    }

    int mid = l + (r - l) / 2;
    query(2 * node + 1, l, mid, index, ans);
    query(2 * node + 2, mid + 1, r, index, ans);

    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

int main() {
    int n, q; cin >> n >> q;

    while(q--) {
        int type; cin >> type;
        if(type == 1) {
            int left, right, value; cin >> left >> right >> value;
            update(0, 0, n - 1, left, right - 1, value);
        } else {
            int index; i64 ans = 0; cin >> index;
            query(0, 0, n - 1, index, ans);
            cout << ans << "\n";
        }
    }
    return 0;
}
