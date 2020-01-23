/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We need to calculate X = sum((i - l + 1) ^ k * a[i]) (l <= i <= r)
        - X = (i + (1-l)) ^ k * a[i]
            = (kC0 * i^k * (1-l)^0 + kC1 * i^(k-1) * (1-l) ^ 1 + ....) * a[i]
        - Use 6 segment tree to store sum(a[i] * i^x) (0 <= x <= 5) with lazy propagation.
        - We can easily query the result and update the tree.
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN];
ll sum[6][MAXN], C[10][10];
ll t[6][MAXN * 8], laz[MAXN * 8];

ll add(ll a, ll b) {
    return (a + b) % MODBASE;
}

ll mul(ll a, ll b) {
    return a * b % MODBASE;
}

ll sub(ll a, ll b) {
    return (a - b + MODBASE) % MODBASE;
}

void build(int k, int l, int r) {
    if (l == r) {
        // e = l^i
        ll e = 1;
        FOR(i,0,5) {
            t[i][k] = mul(a[l], e);
            e = mul(e, l);
        }
        return;
    }
    int m = (l + r) >> 1;
    build(k*2, l, m);
    build(k*2+1, m+1, r);
    FOR(i,0,5) t[i][k] = add(t[i][k*2], t[i][k*2+1]);
}

ll getSum(int i, int l, int r) {
    return sub(sum[i][r], sum[i][l-1]);
}

void lazyUpdate(int k, int l, int r) {
    if (laz[k] == -1) return;
    FOR(i,0,5) t[i][k] = mul(laz[k], getSum(i, l, r));
    if (l < r) {
        // completely remove old lazy value in the child node
        laz[k*2] = laz[k];
        laz[k*2+1] = laz[k];
    }
    laz[k] = -1;
}

void update(int k, int l, int r, int u, int v, int c) {
    lazyUpdate(k,l,r);
    if (l > r || r < u || v < l) return;
    if (u <= l && r <= v) {
        laz[k] = c;
        lazyUpdate(k,l,r);
        return;
    }
    int m = (l + r) >> 1;
    update(k*2, l, m, u, v, c);
    update(k*2+1, m+1, r, u, v, c);
    FOR(i,0,5) t[i][k] = add(t[i][k*2], t[i][k*2+1]);
}

ll get(int e, int k, int l, int r, int u, int v) {
    lazyUpdate(k,l,r);
    if (l > r || r < u || v < l) return 0;
    if (u <= l && r <= v) return t[e][k];
    int m = (l + r) >> 1;
    return add(get(e, k*2, l, m, u, v), get(e, k*2+1, m+1, r, u, v));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];
    build(1,1,n);

    // sum[j][i] = 1^j + 2^j + ... + i^j
    FOR(i,1,n) {
        ll e = 1;
        FOR(j,0,5) {
            sum[j][i] = add(sum[j][i-1], e);
            e = mul(e, i);
        }
    }

    // C[n][k] = nCk
    FOR(i,0,5)
        FOR(j,0,i)
            if (j == 0 || j == i) C[i][j] = 1;
            else C[i][j] = C[i-1][j] + C[i-1][j-1];

    // init lazy tree
    FOR(i,0,800000) laz[i] = -1;
    while (m--) {
        char ch;
        int u, v, c;
        cin >> ch >> u >> v >> c;
        if (ch == '=') update(1,1,n,u,v,c);
        else {
            // calculate the result
            ll res = 0, x = sub(1, u);
            ll e = 1;
            FOR(i,0,c) {
                res = add(res, mul(C[c][i], mul(get(c-i, 1, 1, n, u, v), e)));
                e = mul(e, x);
            }
            cout << res << "\n";
        }
    }
    return 0;
}
