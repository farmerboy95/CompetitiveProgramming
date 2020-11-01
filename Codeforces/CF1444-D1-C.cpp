/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Dividing a number of nodes into 2 sets that there is no edge connecting 2 nodes in the
        same set, sounds familiar? Yes, it's bipartite graph.
        - So the problem reduced to: Given an undirected graph without loops and multiple edges, 
        each vertex has some color from 1 to k. Count the number of pairs of colors such that 
        graph induced by vertices of these two colors will be bipartite.
        - The combined one should be bipartite, so for each color, its graph should also be bipartite.
        - There are k*(k-1)/2 pairs of groups, right? Sounds TLE but we can handle pairs of groups
        that have edges connecting those groups and if it's not bipartite, we can subtract 1 from
        the answer. By the way, we are counting all of the pairs first, then we subtract all the
        unsatisfied pairs using the above check and pairs check.
        - Let's check one pair of groups. How can we check if adding edges connecting those 2 will
        not make the graph not bipartite? We can use something like DSU with rollback (reversible DSU).
        - Ok, so for bipartite graph, it can be colored as we all know, the color does not matter
        and there are 2 ways to color it, use 0 or 1 at an arbitrary node.
        - We do the same way here, let node u represents the node u itself if we color it 0, and
        node n+u represents the node u if we color it 1.
        - So when merging 2 nodes, we merge (u, n+v) and (v, n+u). The graph is not bipartite when
        u and v are on the same side, or in other words, they are in the same connected component
        in DSU.
        - Firstly, if a graph of a color is bipartite, we can add edges of it to DSU. When we consider
        a pairs of colors, we can add edges and check if it's still bipartite. After being done with
        it we rollback the changes to consider the next pair.

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
const int MAXN = 500010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

vector<int> a[MAXN];
int n, m, k, gr[MAXN], remain, ok[MAXN];
vector<II> edges;
map<II, vector<II> > ma;

vector<II> st;
int lab[MAXN*2], sz[MAXN*2];

int getRoot(int u) {
    while (lab[u] != u) u = lab[u];
    return u;
}

void unionPair(int u, int v) {
    u = getRoot(u);
    v = getRoot(v);
    if (u == v) {
        st.push_back(II(-1, -1));
        return;
    }
    if (sz[u] < sz[v]) swap(u, v);
    st.push_back(II(u, v));
    sz[u] += sz[v];
    lab[v] = u;
}

bool check(int u, int v) { return getRoot(u) == getRoot(v); }

void rollback(int cnt) {
    while (cnt--) {
        II x = st.back();
        st.pop_back();
        if (x.SE == -1) continue;
        lab[x.SE] = x.SE;
        sz[x.FI] -= sz[x.SE];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    FOR(i,1,n) {
        cin >> gr[i];
    }
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        edges.push_back(II(u, v));
    }
    FOR(i,1,2*n) {
        lab[i] = i;
        sz[i] = 1;
    }
    ll res = (ll) k * (k-1) / 2;
    remain = k;
    FOR(i,1,k) ok[i] = true;

    FOR(i,0,m-1) {
        int u = edges[i].FI, v = edges[i].SE;
        if (gr[u] == gr[v]) {
            unionPair(u, n+v);
            unionPair(v, n+u);
            if (check(u, v)) {
                if (ok[gr[u]]) {
                    res -= remain-1;
                    remain--;
                    ok[gr[u]] = false;
                }
            }
        } else {
            int U = gr[u], V = gr[v];
            if (U > V) swap(U, V);
            if (ok[U] && ok[V]) ma[II(U, V)].push_back(edges[i]);
        }
    }
    
    FORALL(it, ma) {
        II w = it->FI;
        if (!ok[w.FI] || !ok[w.SE]) continue;
        bool co = true;
        int cnt = 0;
        for (II x : it->SE) {
            int u = x.FI, v = x.SE;
            unionPair(u, n+v);
            unionPair(v, n+u);
            cnt += 2;
            if (check(u, v)) {
                co = false;
                break;
            }
        }
        if (!co) res--;
        rollback(cnt);
    }
    cout << res;
    return 0;
}
