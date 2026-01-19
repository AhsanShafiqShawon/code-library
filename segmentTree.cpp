#include<bits/stdc++.h>
#define i64 long long
using namespace std;
const int N = 1e5 + 5;
i64 tree[4 * N]; int a[N];

void build(int node, int l, int r) {
    if(l == r) {
        tree[node] = a[l]; return;
    }

    int mid = l + (r - l) / 2;
    build(2 * node + 1, l, mid);
    build(2 * node + 2, mid + 1, r);
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

i64 query(int node, int l, int r, int b, int e) {
    if(e < l or r < b) return 0;
    if(b <= l and r <= e) return tree[node];

    int mid = l + (r - l) / 2;
    return query(2 * node + 1, l, mid, b, e) + query(2 * node + 2, mid + 1, r, b, e);
}

void update(int node, int index, int value, int l, int r) {
    if(index < l or index > r) return;
    if(l == index and r == index) {
        tree[node] = value; return;
    }

    int mid = l + (r - l) / 2;
    update(2 * node + 1, index, value, l, mid);
    update(2 * node + 2, index, value, mid + 1, r);

    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

int main() {
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> a[i];

    build(0, 0, n - 1);

    while(q--) {
        int type; cin >> type;
        if(type == 1) {
            int index, value; cin >> index >> value;
            update(0, index, value, 0, n - 1);
        } else {
            int left, right; cin >> left >> right;
            cout << query(0, 0, n - 1, left, right - 1) << "\n";
        }
    }
    return 0;
}
