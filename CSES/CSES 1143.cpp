/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Hotel Queries
        - Trivial Segment tree problem.
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

struct SegmentTree {
    public:
    int N;

    // 0-indexed
    SegmentTree(int n) {
        t.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) t[i] = 0;
    }

    SegmentTree(vector<int> &a) {
        t.resize(4*SZ(a));
        N = SZ(a);
        build(1, 0, N-1, a);
    }

    int get(int k, int l, int r, int u, int v) {
        if (l > r || r < u || v < l) return 0;
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        int lef = get(k*2, l, m, u, v);
        int rig = get(k*2+1, m+1, r, u, v);
        return max(lef, rig);
    }

    void update(int k, int l, int r, int u, int val) {
        if (l > r || r < u || u < l) return;
        if (l == r) {
            t[k] = val;
            return;
        }
        int m = (l + r) >> 1;
        update(k*2, l, m, u, val);
        update(k*2+1, m+1, r, u, val);
        t[k] = max(t[k*2], t[k*2+1]);
    }

    int find(int k, int l, int r, int val) {
        if (l == r) {
            if (t[k] >= val) {
                t[k] -= val;
                return l;
            }
            return -1;
        }
        int m = (l + r) >> 1;
        int res = -1;
        if (t[k*2] >= val) res = find(k*2, l, m, val);
        else if (t[k*2+1] >= val) res = find(k*2+1, m+1, r, val);
        t[k] = max(t[k*2], t[k*2+1]);
        return res;
    }

    private:
    vector<int> t;

    void build(int k, int l, int r, vector<int> &a) {
        if (l > r) return;
        if (l == r) {
            t[k] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(k*2, l, m, a);
        build(k*2+1, m+1, r, a);
        t[k] = max(t[k*2], t[k*2+1]);
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
        int x;
        cin >> x;
        cout << st.find(1,0,st.N-1,x)+1 << ' ';
    }
    return 0;
}
