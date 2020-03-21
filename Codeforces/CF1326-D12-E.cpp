/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Mainly from https://codeforces.com/blog/entry/74961
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
const int MAXN = 300010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, p[MAXN], pos[MAXN], q[MAXN], t[MAXN * 8], lazy[MAXN * 8];

void build(int k, int l, int r) {
    if (l > r) return;
    if (l == r) {
        if (l <= pos[n]) t[k] = 1;
        return;
    } 
    int m = (l + r) >> 1;
    build(k*2,l,m);
    build(k*2+1,m+1,r);
    t[k] = max(t[k*2], t[k*2+1]);
}

void lazyUpdate(int k, int l, int r) {
    if (lazy[k] == 0) return;
    t[k] += lazy[k];
    if (l < r) {
        lazy[k*2] += lazy[k];
        lazy[k*2+1] += lazy[k];
    }
    lazy[k] = 0;
}

void update(int k, int l, int r, int u, int v, int val) {
    lazyUpdate(k,l,r);
    if (l > r || r < u || v < l) return;
    if (u <= l && r <= v) {
        lazy[k] += val;
        lazyUpdate(k,l,r);
        return;
    }
    int m = (l + r) >> 1;
    update(k*2, l, m, u, v, val);
    update(k*2+1, m+1, r, u, v, val);
    t[k] = max(t[k*2], t[k*2+1]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    FOR(i,1,n) cin >> q[i];
    // build segment tree (get max b[i] in editorial) with x == n first, so b[i] = 1 if
    // i <= pos[n], otherwise b[i] = 0, t[k] is max segment b[i] that k manages.
    build(1,1,n);
    int x = n;
    // print result of the case that has no bomb
    cout << x << ' ';
    FOR(i,1,n-1) {
        // add the bomb to segment tree
        update(1,1,n,1,q[i],-1);
        // max(b[i]) <= 0 (1 <= i <= n), it means result < x, so we decrease x
        // and add increase segment from 1 to new x
        while (t[1] <= 0) {
            x--;
            int k = pos[x];
            update(1,1,n,1,k,1);
        }
        cout << x << ' ';
    }
    return 0;
}
