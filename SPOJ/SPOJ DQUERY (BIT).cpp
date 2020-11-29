/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Consider an ending point r, if we store f[i] = 1 as the last appearance of a[i] in the
        array a[1...r], we can get result of query (l, r) = sum(f[i]) (i = 1...r) - sum(f[i]) 
        (i = 1...l-1).
        - So we can sort the queries in the increasing order of r, and we add n queries to add
        new a[i] as well, and maintain a BIT to simulate the above formula.
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
const int MAXN = 200010;
const int MAXM = 1000010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, q, a[MAXN], res[MAXN], pos[MAXM];

struct Query {
    int l, r, cs;
    Query(int l = 0, int r = 0, int cs = 0) : l(l), r(r), cs(cs) {}
    bool operator< (const Query &q) const {
        if (r != q.r) return r < q.r;
        return l < q.l;
    }
};

vector<Query> b;

struct BinaryIndexedTree {
    public:
    // 1-indexed
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i];
        b.push_back(Query(0, i, 0));
    }
    cin >> q;
    FOR(i,1,q) {
        int u, v;
        cin >> u >> v;
        b.push_back(Query(u, v, i));
    }
    sort(ALL(b));

    BinaryIndexedTree bit(MAXM);
    for (Query qu : b) {
        if (qu.l == 0) {
            if (pos[a[qu.r]] == 0) {
                bit.update(qu.r, 1);
            } else {
                bit.update(pos[a[qu.r]], -1);
                bit.update(qu.r, 1);
            }
            pos[a[qu.r]] = qu.r;
        } else {
            res[qu.cs] = bit.get(qu.r) - bit.get(qu.l-1);
        }
    }


    FOR(i,1,q) cout << res[i] << "\n";
    return 0;
}
