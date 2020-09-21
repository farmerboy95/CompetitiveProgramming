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

Data op(Data &a, Data &b) { 
    return Data(b.a * a.a % MOD, (b.b + b.a * a.b) % MOD);
}

Data e() { return Data(1, 0); }

// <data, merging operation, default value>
template <class S, S (*op)(S&, S&), S (*e)()>
struct SegmentTree {
  public:
    SegmentTree() : SegmentTree(0) {}
    SegmentTree(int n) : SegmentTree(vector<S>(n, e())) {}
    SegmentTree(const vector<S>& v) : _n(int(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = vector<S>(2 * size, e());
        FOR(i,0,_n-1) d[size + i] = v[i];
        FORE(i,size-1,1) update(i);
    }

    // set a[p] = x
    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    // get a[p]
    S get(int p) {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    // query in [l, r)
    S query(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

  private:
    int _n, size, log;
    vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

    int ceil_pow2(int p) {
        int x = 0;
        while ((1U << x) < (unsigned int)(p)) x++;
        return x;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<Data> a(n);
    FOR(i,0,n-1) {
        int u, v;
        cin >> u >> v;
        a[i] = Data(u, v);
    }
    SegmentTree<Data, op, e> st(a);
    while (q--) {
        int ch, u, v, c;
        cin >> ch >> u >> v >> c;
        if (ch == 0) {
            st.set(u, Data(v, c));
        } else {
            Data w = st.query(u, v);
            cout << w.get(c) << "\n";
        }
    }
    return 0;
}
