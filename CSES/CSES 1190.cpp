/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Subarray Sum Queries
        - Classic Segment Tree with each node storing sum, bestSum, bestPrefixSum and bestSuffixSum
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
    ll sum, bestSum, bestSumPrefix, bestSumSuffix;
    Data(ll sum = 0, ll a = 0, ll b = 0, ll c = 0) : sum(sum), bestSum(a), bestSumPrefix(b), bestSumSuffix(c) {}
};

struct SegmentTree {
    public:
    int N;

    // 0-indexed
    SegmentTree(int n) {
        t.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) t[i] = Data();
    }

    SegmentTree(vector<int> &a) {
        t.resize(4*SZ(a));
        N = SZ(a);
        build(1, 0, N-1, a);
    }

    Data get(int k, int l, int r, int u, int v) {
        if (l > r || r < u || v < l) return Data();
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        Data lef = get(k*2, l, m, u, v);
        Data rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
    }

    void update(int k, int l, int r, int u, int val) {
        if (l > r || r < u || u < l) return;
        if (l == r) {
            if (val >= 0) t[k] = Data(val, val, val, val);
            else t[k] = Data(val, 0, 0, 0);
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, val);
        update(k*2+1, m+1, r, u, val);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    private:
    vector<Data> t;

    void build(int k, int l, int r, vector<int> &a) {
        if (l > r) return;
        if (l == r) {
            if (a[l] >= 0) t[k] = Data(a[l], a[l], a[l], a[l]);
            else t[k] = Data(a[l], 0, 0, 0);
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m, a);
        build(k*2+1, m+1, r, a);
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    Data merge(Data &a, Data &b) {
        Data res;
        res.sum = a.sum + b.sum;
        res.bestSumPrefix = max(a.sum + b.bestSumPrefix, a.bestSumPrefix);
        res.bestSumSuffix = max(b.sum + a.bestSumSuffix, b.bestSumSuffix);
        res.bestSum = max(a.bestSum, b.bestSum);
        res.bestSum = max(res.bestSum, a.bestSumSuffix + b.bestSumPrefix);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    FOR(i,0,n-1) cin >> a[i];
    SegmentTree st(a);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;
        st.update(1,0,st.N-1,u,v);
        Data res = st.get(1,0,st.N-1,0,st.N-1);
        cout << res.bestSum << "\n";
    }
    return 0;
}
