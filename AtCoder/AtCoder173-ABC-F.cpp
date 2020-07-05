/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's consider R from 1 to N. We will calculate sum of f(L, R) (1 <= L <= R) for each R.
        - So for each R, we consider its adjacent nodes, named v. We don't care about v > R as we 
        are calculating inside [1, R] range.
        - What about nodes v that v < R? The edge would reduce the number of connected component by
        one if L <= v, clearly.
        - Ok, now we build a segment tree, the leaf manages segment (L, L) stores the number of 
        connected components of f(L, R). We would consider R from 1 to N and update it for each R.
        - When we move from R = i-1 to R = i, we have a new node for each graph from 1 to R, so
        we add 1 to each graph from 1 to i. Then for each nodes v adjacent to R, if v < R, we subtract
        1 from each graph from 1 to v. Then to get the result for R, we simply get sum(1, N) (as the
        value > R will be 0 anyway).
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define EPS 1e-9
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
vector<int> a[MAXN];
ll t[MAXN * 8], lazy[MAXN * 8];

void build(int k, int l, int r) {
    if (l > r) return;
    if (l == r) {
        t[k] = 0;
        return;
    }
    int m = (l + r) >> 1;
    build(k*2, l, m);
    build(k*2+1, m+1, r);
    t[k] = t[k*2] + t[k*2+1];
}

void lazyUpdate(int k, int l, int r) {
    if (l > r) return;
    if (lazy[k] == 0) return;
    t[k] += lazy[k] * (r - l + 1);
    if (l < r) {
        lazy[k*2] += lazy[k];
        lazy[k*2+1] += lazy[k];
    }
    lazy[k] = 0;
}

void update(int k, int l, int r, int u, int v, int val) {
    lazyUpdate(k, l, r);
    if (l > r || r < u || v < l) return;
    if (u <= l && r <= v) {
        lazy[k] += val;
        lazyUpdate(k, l, r);
        return;
    }
    int m = (l + r) >> 1;
    update(k*2, l, m, u, v, val);
    update(k*2+1, m+1, r, u, v, val);
    t[k] = t[k*2] + t[k*2+1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    build(1,1,n);

    ll res = 0;
    FOR(i,1,n) {
        update(1,1,n,1,i,1);
        FOR(j,0,SZ(a[i])-1) {
            int v = a[i][j];
            if (v < i) update(1,1,n,1,v,-1);
        }
        res += t[1];
    }
    cout << res;
    return 0;
}
