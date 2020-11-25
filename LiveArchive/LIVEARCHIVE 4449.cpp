/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let nodes of type A be the nodes X for which the route 1 -> X has a constant distance, 
        no matter which path we take. Similarly, let nodes of type B be the nodes X for which 
        the route X -> N has a constant distance, no matter which path we take.
        - Clearly, all nodes must be either be of type A or type B, or the answer is No solution 
        (we can't fix both 1->X and X->N paths with a single toll). This condition also turns out 
        to be sufficient -- if all nodes of either type A or type B, we can fix all distances by 
        tolling every A->B road.
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
const int MAXN = 50010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, degIn[MAXN], degOut[MAXN], toST[MAXN], diffST[MAXN], toED[MAXN], diffED[MAXN];
vector<III> edges;
vector<II> a[2][MAXN];

void solve() {
    MS(diffST, 0);
    MS(toST, 0);
    MS(diffED, 0);
    MS(toED, 0);

    queue<int> q;
    q.push(1);

    // toST[u] = longest path from 1 to u
    // diffST[u] = whether we have multiple length path from 1 to u
    while (SZ(q)) {
        int u = q.front(); q.pop();
        for (auto e : a[0][u]) {
            if (toST[e.FI] && toST[e.FI] != toST[u] + e.SE) diffST[e.FI] = 1;
            diffST[e.FI] |= diffST[u];
            toST[e.FI] = max(toST[e.FI], toST[u] + e.SE);
            if (--degIn[e.FI] == 0) q.push(e.FI);
        }
    }

    q.push(n);

    // toED[u] = longest path from n to u
    // diffED[u] = whether we have multiple length path from n to u
    while (SZ(q)) {
        int u = q.front(); q.pop();
        for (auto e : a[1][u]) {
            if (toED[e.FI] && toED[e.FI] != toED[u] + e.SE) diffED[e.FI] = 1;
            diffED[e.FI] |= diffED[u];
            toED[e.FI] = max(toED[e.FI], toED[u] + e.SE);
            if (--degOut[e.FI] == 0) q.push(e.FI);
        }
    }

    // Clearly, all nodes must be either be of type A or type B, or the answer is No solution
    FOR(i,1,n)
        if (diffST[i] && diffED[i]) {
            cout << "No solution\n";
            return;
        }

    // tolling A->B edges
    vector<II> res;
    FOR(i,0,m-1) {
        int u = edges[i].FI.FI, v = edges[i].FI.SE, c = edges[i].SE;
        if (diffST[u] == 0 && diffST[v]) {
            int diff = toST[n] - (toST[u] + toED[v] + c);
            if (diff > 0) res.push_back(II(i+1, diff));
        }
    }
    cout << SZ(res) << ' ' << toST[n] << "\n";
    for (II x : res) cout << x.FI << ' ' << x.SE << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int o = 0;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        o++;
        edges.clear();
        FOR(i,1,n) {
            a[0][i].clear();
            a[1][i].clear();
            degIn[i] = degOut[i] = 0;
        }
        FOR(i,1,m) {
            int u, v, c;
            cin >> u >> v >> c;
            a[0][u].push_back(II(v, c));
            a[1][v].push_back(II(u, c));
            edges.push_back(III(II(u, v), c));
            degIn[v]++;
            degOut[u]++;
        }

        cout << "Case " << o << ": ";
        solve();
    }
    return 0;
}
