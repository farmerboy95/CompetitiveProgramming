/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For a distance d, if we create a graph with edges connecting points that have distance d
        between them, the graph is bipartite. Let's prove it.

        - To prove that the graph is a bipartite graph it is sufficient to prove that it doesn't 
        have any odd length cycle.
        - Case 1: d is odd.
            + There can be a few pair of (a, b) that a^2 + b^2 = d^2. For all such pairs, (a + b) % 2
            will be 1, clearly.
            + Color the vertices based on (x + y) % 2 (black / white). Since there can't be any edge
            between two same color vertices as the parity of (x, y) and (x + a, y + b) is different.
            Hence the graph is bipartite graph.
            + In other way: we want to show that an odd cycle can't exist. Consider any cycle, each 
            of its edges has some x-translation and y-translation let's say a[i], b[i] respectively.
            We have, a[i]^2 + b[i]^2 = d^2, sum(a[i]) = sum(b[i]) = 0.
            + Since sum(a[i]) = 0, therefore even number of edges have odd a[i], and even number of
            edges have odd b[i]. Since exactly one of a[i] or b[i] os odd, hence the total number of
            edges is always even.
        - Case 2: d is even.
            + Since d is even and a[i]^2 + b[i]^2 = d^2. Either both a[i] and b[i] are both odd or
            both even.
            + Sub case 1: a[i] and b[i] are both odd. (a[i]^2 + b[i]^2) mod 4 = 2, but d^2 mod 4 = 0.
            Hence this case is not possible.
            + Sub case 2: a[i] and b[i] are both odd. Transform the coordinate axis (x, y) -> (x/2, y/2)
            and this case will reduce to some other case.
        
        - Ok, since we have a bipartite graph for a distance d, we now have 2 bipartite graph for d1
        and d2.
        - So in one graph, each point in the plane belongs to one part of the graph, let's name one
        side is 0 and another side is 1. We have 2 graphs. So each point in the plane belongs to 2 sides
        (in 4 sides / sets). So we just pick the largest set, and the total number of points is 4n^2.
        The largest set size should be certainly larger than 4n^2 / 4 = n^2.
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

int n, d1, d2, group[MAXN], color[MAXN], cnt[10];
vector<int> edge[2][MAXN];
bool visited[MAXN];

int dist(II a, II b) {
    return (a.FI - b.FI) * (a.FI - b.FI) + (a.SE - b.SE) * (a.SE - b.SE);
}

// build 2 graphs
void build(int d, int cs) {
    vector<II> a;
    FOR(i,-n,n)
        FOR(j,-n,n)
            if (i * i + j * j == d) a.push_back(II(i, j));
    FOR(i,0,n-1)
        FOR(j,0,n-1)
            for (II x : a) {
                int u = i + x.FI, v = j + x.SE;
                if (u >= 0 && u < n && v >= 0 && v < n) edge[cs][n * i + j].push_back(n * u + v);
            }
}

void dfs(int u, int col, int hs) {
    visited[u] = true;
    color[u] += hs * col;
    for (int v : edge[hs-1][u])
        if (!visited[v]) dfs(v, 1-col, hs);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> d1 >> d2;
    // plane size is 2*n
    n <<= 1;
    build(d1, 0);
    build(d2, 1);

    // coloring the graph in first graph
    FOR(i,0,n*n-1)
        if (!visited[i]) dfs(i, 0, 1);
    MS(visited, false);
    // coloring the graph in second graph, combining with the first one
    FOR(i,0,n*n-1)
        if (!visited[i]) dfs(i, 0, 2);

    // count number of points in each set
    FOR(i,0,n*n-1) cnt[color[i]]++;
    int res = 0, Max = 0, dem = 0;
    // get the largest set
    FOR(i,0,3)
        if (cnt[i] > Max) {
            Max = cnt[i];
            res = i;
        }
    FOR(i,0,n-1)
        FOR(j,0,n-1)
            if (color[n*i+j] == res) {
                cout << i << ' ' << j << "\n";
                dem++;
                // print n^2 points only
                if (dem * 4 == n * n) return 0;
            }
    return 0;
}
