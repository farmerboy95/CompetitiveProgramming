/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We first need to find the indices of queries after all numbers are added to the array.
        - We maintain a Binary Indexed Tree, fill it with 1 first. We will consider queries reversely
        - So here is the thing, when trying to find the final index of an index, we binary search
        to find the number of remaining indices that are smaller than or equal to the index that
        we are considering. After finding it, we update the index. We can remove it from BIT (type A) 
        if needed. For example 1 1 0 0 1, we need to find the one that has index 3, which one? should
        be the fifth one as the number of remaining indices from index 5 to 1 is 3.
        - After finding all final indices, we can proceed with queries using Segment Tree.
        - Complexity O(n * logn * logn)
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

    SegmentTree(int n) {
        t.resize(4*n);
        N = n;
        FOR(i,0,SZ(t)-1) t[i] = -1000000001;
    }

    SegmentTree(vector<ll> &a) {
        t.resize(4*SZ(a));
        N = SZ(a);
        build(1, 0, N-1, a);
    }

    ll merge(ll &a, ll &b) {
        return a > b ? a : b;
    }

    ll get(int k, int l, int r, int u, int v) {
        if (l > r || r < u || v < l) return -1000000001;
        if (u <= l && r <= v) return t[k];
        int m = (l + r) >> 1;
        ll lef = get(k*2, l, m, u, v);
        ll rig = get(k*2+1, m+1, r, u, v);
        return merge(lef, rig);
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
        t[k] = merge(t[k*2], t[k*2+1]);
    }

    private:
    vector<ll> t;

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
};

struct BinaryIndexedTree {
    public:
    BinaryIndexedTree(int n) {
        N = n;
        t.resize(N+1);
        FOR(i,0,N) t[i] = 0;
    }

    void update(int u, int val) {
        while (u <= N) {
            t[u] += val;
            u = u + (u & (-u));
        }
    }
 
    int get(int u) {
        int res = 0;
        while (u) {
            res += t[u];
            u = u - (u & (-u));
        }
        return res;
    }

    private:
    vector<int> t;
    int N;
};

struct Query {
    int ch, x, y;
    Query(int ch = 0, int x = 0, int y = 0) : ch(ch), x(x), y(y) {}
};

int binarySearch(int u, int n, BinaryIndexedTree &bit) {
    int dau = 1, cuoi = n;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (bit.get(mid) >= u) cuoi = mid-1;
        else dau = mid+1;
    }
    return dau;
}

vector<Query> q;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m;
    cin >> m;
    n = 0;
    FOR(i,1,m) {
        char ch;
        int x, y;
        cin >> ch >> x >> y;
        if (ch == 'A') q.push_back(Query(1, y, x));
        else q.push_back(Query(ch, x, y));
        if (ch == 'A') n++;
    }

    BinaryIndexedTree bit(n);
    FOR(i,1,n) bit.update(i, 1);

    FORE(i,SZ(q)-1,0)
        if (q[i].ch == 1) {
            // insert number
            int x = binarySearch(q[i].x, n, bit);
            bit.update(x, -1);
            q[i].x = x;
        } else {
            // get max
            q[i].x = binarySearch(q[i].x, n, bit);
            q[i].y = binarySearch(q[i].y, n, bit);
        }

    SegmentTree st(n);
    FOR(i,0,SZ(q)-1)
        if (q[i].ch == 1) {
            st.update(1,0,st.N-1,q[i].x-1,q[i].y);
        } else {
            cout << st.get(1,0,st.N-1,q[i].x-1,q[i].y-1) << "\n";
        }
    return 0;
}
