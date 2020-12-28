/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Polynomial Queries
        - https://codeforces.com/blog/entry/78923?#comment-643208
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

struct Data {
    ll add, fi;
    Data(ll add = 0, ll fi = 0) : add(add), fi(fi) {}
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
            lazy[i] = Data();
        }
    }

    SegmentTreeLazy(vector<ll> &a) {
        t.resize(4*SZ(a));
        lazy.resize(4*SZ(a));
        N = SZ(a);
        build(1, 0, N-1, a);
        FOR(i,0,SZ(t)-1) lazy[i] = Data();
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
        if (lazy[k].add == 0 && lazy[k].fi == 0) return;
        t[k] += (ll) (r-l+1) * lazy[k].add;
        t[k] += (ll) (r-l+1) * (2LL * lazy[k].fi + (ll) (r-l) * lazy[k].fi) / 2;
        if (l < r) {
            mergeLazy(lazy[k*2], lazy[k]);
            int len = ((l + r) >> 1) - l + 1;
            mergeLazy(lazy[k*2+1], Data(lazy[k].add + len * lazy[k].fi, lazy[k].fi));
        }
        lazy[k] = Data();
    }

    void update(int k, int l, int r, int u, int v) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return;
        if (u <= l && r <= v) {
            lazy[k] = Data(l-u, 1);
            lazyUpdate(k, l, r);
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, v);
        update(k*2+1, m+1, r, u, v);
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
        return a+b;
    }

    void mergeLazy(Data &ol, Data ne) {
        ol.add += ne.add;
        ol.fi += ne.fi;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    FOR(i,0,n-1) cin >> a[i];
    SegmentTreeLazy st(a);
    while (m--) {
        int ch, u, v;
        cin >> ch >> u >> v;
        u--;
        v--;
        if (ch == 1) {
            st.update(1,0,st.N-1,u,v);
        } else {
            cout << st.get(1,0,st.N-1,u,v) << "\n";
        }
    }
    return 0;
}
