/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 
        - Since MST's are created from the smallest edge weights, if an MST contains 
        edges with weight X, it must also contain all edges with weights less than X 
        (as long as the edges with lesser weights don't form cycles).
        - For each query, we group the edges in the query by the weights. For each edge group, 
        if the edges in that group form a cycle with all other edges with lesser weights, 
        then the answer to the corresponding query is no, because MSTs don't have cycles. 
        If none of the edge groups form cycles, then the answer to the query is yes.
        - To do this efficiently, we have to sort the edge groups by weight and process 
        the edge groups starting from the lower ones, while maintaining disjoint sets 
        for nodes connected by edges with lower weights (by comparing weight-sorted initial edges with 
        current edge group).
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

struct Edge {
    int u, v, w, cs;
    Edge(int u = 0, int v = 0, int w = 0, int cs = 0) : u(u), v(v), w(w), cs(cs) {}
};

bool operator< (const Edge &a, const Edge &b) {
    return a.w < b.w;
}

struct Block {
    vector<Edge> e;
    int w, cs;
};

bool operator< (const Block &a, const Block &b) {
    return a.w < b.w;
}

int n, ord[MAXN], ptr, lab[MAXN], m;
Edge a[MAXN];
Block b[MAXN];
vector<int> A[MAXN];
bool visited[MAXN], res[MAXN];

int getRoot(int u) {
    while (lab[u] > 0) u = lab[u];
    return u;
}

void unionPair(int u, int v) {
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[v] = u;
        lab[u] = x;
    }
    else {
        lab[u] = v;
        lab[v] = x;
    }
}

bool inCycle(int u, int p) {
    visited[u] = true;
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (v == p) continue;
        if (visited[v]) return true;
        if (inCycle(v, u)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) lab[i] = -1;

    // sort edges in increasing order
    FOR(i,1,m) {
        cin >> a[i].u >> a[i].v >> a[i].w;
        a[i].cs = i;
    }
    sort(a+1, a+m+1);
    FOR(i,1,m) ord[a[i].cs] = i;

    // divide each query into blocks of same weight
    // put each block into array of blocks and sort them in increasing order
    int q;
    cin >> q;
    FOR(i,1,q) {
        res[i] = true;
        int k;
        cin >> k;
        vector<Edge> v(k);
        FOR(j,1,k) {
            int x;
            cin >> x;
            v[j-1] = a[ord[x]];
        }
        sort(ALL(v));
        FOR(j,0,k-1) {
            if (j == 0 || v[j].w != v[j-1].w) {
                vector<Edge> z;
                b[++ptr] = {z, v[j].w, i};
            }
            b[ptr].e.emplace_back(v[j]);
        }
    }
    sort(b+1, b+ptr+1);

    // iterate through blocks and consider adding edges into MST at the same time
    int t = 1;
    FOR(i,1,ptr) {
        while (a[t].w < b[i].w) {
            int U = getRoot(a[t].u);
            int V = getRoot(a[t].v);
            if (U != V) unionPair(U, V);
            t++;
        }

        set<int> relatedNodes;
        FOR(j,0,SZ(b[i].e)-1) {
            int u = b[i].e[j].u;
            int v = b[i].e[j].v;
            int U = getRoot(u);
            int V = getRoot(v);
            relatedNodes.insert(U); relatedNodes.insert(V);
            A[U].emplace_back(V); A[V].emplace_back(U);
        }

        // simple dfs to know whether this block can create a cycle or not
        // only need to add root of the tree of each point into the new graph
        // if the block creates cycle(s), we simply set the result of the query which it is belonged to is NO
        FORALL(it, relatedNodes) {
            int u = *it;
            if (!visited[u] && inCycle(u, -1)) res[b[i].cs] = false;
        }

        FORALL(it, relatedNodes) {
            int u = *it;
            A[u].clear();
            visited[u] = false;
        }
        relatedNodes.clear();
    }

    FOR(i,1,q)
        if (res[i]) cout << "YES\n";
        else cout << "NO\n";
    return 0;
}
