/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Range Updates and Sums
        - Prioritize query 2 (set) and take summation of query 1 (add)
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
    ll add, se;
    Data(ll add = 0, ll se = 0) : add(add), se(se) {}
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

    SegmentTreeLazy(vector<int> &a) {
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
        if (lazy[k].add == 0 && lazy[k].se == 0) return;
        if (lazy[k].se > 0) t[k] = (ll) (r - l + 1) * lazy[k].se;
        t[k] += (ll) (r - l + 1) * lazy[k].add;
        if (l < r) {
            mergeLazy(lazy[k*2], lazy[k]);
            mergeLazy(lazy[k*2+1], lazy[k]);
        }
        lazy[k] = Data();
    }

    void update(int k, int l, int r, int u, int v, II val) {
        lazyUpdate(k, l, r);
        if (l > r || r < u || v < l) return;
        if (u <= l && r <= v) {
            if (val.FI == 1) lazy[k].add = val.SE;
            else lazy[k].se = val.SE;
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

    void build(int k, int l, int r, vector<int> &a) {
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

    void mergeLazy(Data &ol, Data &ne) {
        if (ne.se) ol = ne;
        else ol.add += ne.add;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    FOR(i,0,n-1) cin >> a[i];
    SegmentTreeLazy st(a);
    while (m--) {
        int ch, u, v, c;
        cin >> ch >> u >> v;
        u--;
        v--;
        if (ch == 1) {
            cin >> c;
            st.update(1,0,st.N-1,u,v,II(1,c));
        } else if (ch == 2) {
            cin >> c;
            st.update(1,0,st.N-1,u,v,II(2,c));
        } else {
            cout << st.get(1,0,st.N-1,u,v) << "\n";
        }
    }
    return 0;
}
