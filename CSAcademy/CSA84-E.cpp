/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Weight of every edge is a linear function
        - We have n^2 candidates of becoming tree diameter, each candidate is sum of edges' weight => linear function
        - Tree diameter at a day x is max of all linear function, so it would have the following shape
                        \                                      /
                         \                                    /
                          \                                  /
                           \                                /
                            \                              /
                             \                            /
                              ----------------------------
        - We can use ternary search or binary search (find the minimum day that has f(x+1) - f(x) >= 0)
        - Find diameter of a tree at a specific day in O(n)
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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 300010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Edge {
    int des, w, ch;
    Edge(int des = 0, int w = 0, int ch = 0) : des(des), w(w), ch(ch) {}
};

int n, d;
ll res;
vector<Edge> a[MAXN];

ll dfs(int u, int p, int D) {
    ll m1 = 0, m2 = 0;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].des;
        int c = a[u][i].w;
        int ch = a[u][i].ch;
        if (v == p) continue;
        ll m3 = dfs(v, u, D) + c + (ll) ch * D;
        if (m3 > m1) swap(m1, m3);
        if (m3 > m2) swap(m2, m3);
    }
    res = max(res, m1 + m2);
    return m1;
}

ll check(int D) {
    res = 0;
    dfs(1, 0, D);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> d;
    FOR(i,1,n-1) {
        int u, v, c, e;
        cin >> u >> v >> c >> e;
        a[u].emplace_back(Edge(v, c, e));
        a[v].emplace_back(Edge(u, c, e));
    }
    int dau = 0, cuoi = d-1, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        ll x = check(mid), y = check(mid+1);
        if (y >= x) cuoi = mid-1;
        else dau = mid+1;
    }
    check(dau);
    cout << dau << "\n" << res;
    return 0;
}
