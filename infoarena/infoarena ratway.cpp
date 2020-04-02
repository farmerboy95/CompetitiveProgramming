/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - More or less like https://github.com/thecodingwizard/competitive-programming/blob/master/Infoarena/ratway.cpp
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;
multiset<int> a[MAXN];
vector<int> oddDeg, tour;
vector<II> edges;

void eulerTour(int u) {
    while (SZ(a[u])) {
        multiset<int> ::iterator it = a[u].begin();
        int v = *it;
        a[u].erase(it);
        a[v].erase(a[v].find(u));
        eulerTour(v);
        tour.push_back(u);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("ratway.in", "r", stdin);
    freopen("ratway.out", "w", stdout);
    // the final graph must have even number of edges, as one directed edge
    // add 1 to in degree of a node and 1 to out degree of another node

    // for a node in the final graph, in degree and out degree are even
    // if we treat the edges as undirected ones, each node's degree should be even
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[u].insert(v);
        a[v].insert(u);
    }
    // identify odd-degree node and create edges between pairs to clear them
    // as the sum of degree should be even (adding one to each node in an edge), number of nodes in oddDeg should be even too
    FOR(i,1,n)
        if (SZ(a[i]) % 2) oddDeg.push_back(i);
    for (int i = 1; i < SZ(oddDeg); i += 2) {
        a[oddDeg[i-1]].insert(oddDeg[i]);
        a[oddDeg[i]].insert(oddDeg[i-1]);
        m++;
    }
    // if the number of edge so far is odd, simply add an edge connecting one node to itself
    if (m % 2) {
        a[1].insert(1);
        a[1].insert(1);
    }

    // generate an eulerian cycle
    eulerTour(1);
    reverse(ALL(tour));

    // alternate edge directions on the path
    // explanation: https://github.com/MetalBall887/Competitive-Programming/blob/master/infoarena/infoarena%20ratway.cpp
    FOR(i,0,SZ(tour)-1)
        if (i % 2 == 0) edges.push_back(II(tour[i], tour[(i+1) % SZ(tour)]));
        else edges.push_back(II(tour[(i+1) % SZ(tour)], tour[i]));

    cout << SZ(edges) << "\n";
    FOR(i,0,SZ(edges)-1) cout << edges[i].FI << ' ' << edges[i].SE << "\n";
    return 0;
}
