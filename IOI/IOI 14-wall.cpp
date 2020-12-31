/*
    Author: Nguyen Tan Bao
    Statement: https://dmoj.ca/problem/ioi14p2io
    Status: AC
    Idea:
        - One crucial observation is that for a specific position, any cascade of operations 
        applied on it could be simplified to one minimize operation and one maximize operation.
        - For example, applying (here we omit the paramter l, r as we consider operations solely 
        on a specific index):
            + minimize(9), minimize(8), minimize(7) -> minimize(7), maximize(−inf) 
            + minimize(3), maximize(7), minimize(4) -> minimize(4), maximize(4)
        - In general, this observation could be verified by simple induction.
        - With this observation we could now improve the update time. We instead use a
        segment tree (with lazy propagation) to maintain the final operations applied on 
        an interval.
        - More info: https://codeforces.com/blog/entry/13442?#comment-184202
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct DataLazy {
    int opmin, opmax;
    DataLazy(int opmin = 0, int opmax = 0) : opmin(opmin), opmax(opmax) {}
};

struct SegmentTreeLazy {
    public:
    int N;

    // 0-indexed
    SegmentTreeLazy(int n) {
        lazy.resize(4*n);
        N = n;
        FOR(i,0,SZ(lazy)-1) lazy[i] = DataLazy(100000, 0);
    }

    int get(int k, int l, int r, int u) {
        lazyUpdate(k, l, r);
        if (l == r) return min(lazy[k].opmin, lazy[k].opmax);
        int m = (l + r) >> 1;
        if (u <= m) return get(k*2, l, m, u);
        return get(k*2+1, m+1, r, u);
    }

    void lazyUpdate(int k, int l, int r) {
        if (l > r) return;
        if (lazy[k].opmin == 100000 && lazy[k].opmax == 0) return;
        if (l < r) {
            mergeLazy(lazy[k*2], lazy[k]);
            mergeLazy(lazy[k*2+1], lazy[k]);
            lazy[k] = DataLazy(100000, 0);
        }
    }

    void update(int k, int l, int r, int u, int v, int op, int val) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return;
        if (u <= l && r <= v) {
            if (l == r) {
                if (op == 1) mergeLazy(lazy[k], DataLazy(100000, val));
                else mergeLazy(lazy[k], DataLazy(val, 0));
            } else {
                if (op == 1) lazy[k].opmax = val;
                else lazy[k].opmin = val;
                lazyUpdate(k, l, r);
            }
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, v, op, val);
        update(k*2+1, m+1, r, u, v, op, val);
    }

    private:
    vector<DataLazy> lazy;

    void mergeLazy(DataLazy &ol, DataLazy ne) {
        ol.opmin = min(ol.opmin, ne.opmin);
        ol.opmax = min(ol.opmax, ne.opmin);
        
        ol.opmin = max(ol.opmin, ne.opmax);
        ol.opmax = max(ol.opmax, ne.opmax);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    SegmentTreeLazy st(n);

    while (k--) {
        int ch, u, v, c;
        cin >> ch >> u >> v >> c;
        st.update(1,0,st.N-1,u,v,ch,c);
    }
    FOR(i,0,n-1) cout << st.get(1,0,st.N-1,i) << "\n";
    return 0;
}
