/*
    Author: Nguyen Tan Bao
    Statement: https://judge.yosupo.jp/problem/range_affine_range_sum
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

    bool operator== (const Data &d) {
        return a == d.a && b == d.b;
    }
};

struct SegmentTreeLazy {
    public:
    int N;

    // 0-indexed
    SegmentTreeLazy(int n) {
        t.resize(4*n);
        lazy.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) {
            t[i] = 0;
            lazy[i] = Data(1, 0);
        }
    }

    SegmentTreeLazy(vector<ll> &a) {
        t.resize(4*SZ(a));
        lazy.resize(4*SZ(a));
        N = SZ(a);
        build(1, 0, N-1, a);
        FOR(i,0,SZ(t)-1) lazy[i] = Data(1, 0);
    }

    ll get(int k, int l, int r, int u, int v) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return 0;
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        ll lef = get(k*2, l, m, u, v);
        ll rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
    }

    void lazyUpdate(int k, int l, int r) {
        if (l > r) return;
        if (lazy[k] == Data(1, 0)) return;
        t[k] = (t[k] * lazy[k].a + lazy[k].b * (r - l + 1)) % MOD;
        if (l < r) {
            lazy[k*2] = mergeLazy(lazy[k*2], lazy[k]);
            lazy[k*2+1] = mergeLazy(lazy[k*2+1], lazy[k]);
        }
        lazy[k] = Data(1, 0);
    }

    void update(int k, int l, int r, int u, int v, Data val) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return;
        if (u <= l && r <= v) {
            lazy[k] = val;
            lazyUpdate(k, l, r);
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, v, val);
        update(k*2+1, m+1, r, u, v, val);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    private:
    vector<ll> t;
    vector<Data> lazy;

    void build(int k, int l, int r, vector<ll> &a) {
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

    ll merge(ll &a, ll &b) {
        return (a+b) % MOD;
    }

    Data mergeLazy(Data &ol, Data &ne) {
        return Data(ne.a * ol.a % MOD, (ne.b + ne.a * ol.b) % MOD);
    }
};


int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    FOR(i,0,n-1) cin >> a[i];
    SegmentTreeLazy st(a);

    while (q--) {
        int ch, u, v, c, d;
        cin >> ch >> u >> v;
        v--;
        if (ch == 0) {
            cin >> c >> d;
            st.update(1, 0, st.N-1, u, v, Data(c, d));
        } else {
            cout << st.get(1, 0, st.N-1, u, v) << "\n";
        }
    }
    return 0;
}
