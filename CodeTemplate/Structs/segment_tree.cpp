/*
    Author: Nguyen Tan Bao
    Statement: https://judge.yosupo.jp/problem/point_set_range_composite
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

ll MOD = 998244353;

struct Data {
    ll a, b;
    Data(ll a = 0, ll b = 0) : a(a), b(b) {}

    ll get(ll x) {
        return (a * x + b) % MOD;
    }
};

struct SegmentTree {
    public:
    int N;

    SegmentTree(int n) {
        t.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) t[i] = Data(1, 0);
    }

    SegmentTree(vector<Data> &a) {
        t.resize(4*SZ(a));
        N = SZ(a);
        build(1, 0, N-1, a);
    }

    Data get(int k, int l, int r, int u, int v) {
        if (l > r || r < u || v < l) return Data(1, 0);
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        Data lef = get(k*2, l, m, u, v);
        Data rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
    }

    void update(int k, int l, int r, int u, Data val) {
        if (l > r || r < u || u < l) return;
        if (l == r) {
            t[k] = val;
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, val);
        update(k*2+1, m+1, r, u, val);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    private:
    vector<Data> t;

    void build(int k, int l, int r, vector<Data> &a) {
        if (l > r) return;
        if (l == r) {
            t[k] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m, a);
        build(k*2+1, m+1, r, a);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    Data merge(Data &a, Data &b) {
        return Data(b.a * a.a % MOD, (b.b + b.a * a.b) % MOD);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<Data> a(n);
    FOR(i,0,n-1) cin >> a[i].a >> a[i].b;
    SegmentTree st(a);
    while (q--) {
        int ch, u, v, c;
        cin >> ch >> u >> v >> c;
        if (ch == 0) {
            st.update(1, 0, st.N-1, u, Data(v, c));
        } else {
            v--;
            Data res = st.get(1, 0, st.N-1, u, v);
            cout << res.get(c) << "\n";
        }
    }
    return 0;
}
