/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - More or less like AtCoder084-ARC-F
        - When doing the gcd, we can divide numbers by 2, it can reduce our result
        - The rest can be solved using segment tree.
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

// <data, merging operation, default value>
template <class S, S (*op)(S, S), S (*e)()>
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

ll op(ll a, ll b) { 
    while (1) {
        while (a && a%2==0) a /= 2;
        while (b && b%2==0) b /= 2;
        if (a < b) swap(a, b);
        if (b == 0) return a;
        int x = __builtin_clzll(b)-__builtin_clzll(a);
        a ^= b << x;
    }
}

ll e() {
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    cin >> n;
    SegmentTree<ll, op, e> st(n);
    FOR(i,1,n) {
        ll x;
        cin >> x;
        st.set(i-1, x);
    }
    int q, x;
    cin >> q;
    while (q--) {
        ll u, v;
        cin >> x >> u >> v;
        if (x == 1) {
            st.set(u-1, v);
        } else {
            cout << st.query(u-1, v) << "\n";
        }
    }
    return 0;
}
