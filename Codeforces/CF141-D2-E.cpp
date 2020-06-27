/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - In this problem we must find the minimum spanning tree, in which the half of edges are 
        marked with letter 'S'. (there would be (n-1) / 2 S-edges and the same number of M-edges)
        - If n is even, there is no answer (n-1 is odd, no way to divide it by 2)
        - Let's build a spanning tree without S-edges, there are "cnt" connected components in this graph.
        - If cnt-1 > (n-1) / 2, we have to use more S-edges than required to find the answer => -1.
        - So we try to add some S-edges into the above spanning tree (max (n-1) / 2 S-edges), if the 
        graph is still unconnected after we have added enough S-edges to this spanning tree (1) => -1.
        - Easy to see that the above set of S-edges (2) is included in the answer. Let's build another spanning
        tree based on this set of S-edges. Here we consider the input S-edges again and add some edges (3)
        to this spanning tree until there are (n-1) / 2 S-edges in this tree. Then consider the input M-edges
        and add the remaining (n-1) / 2 M-edges to the tree (if possible, otherwise print -1). Then 
        print the result.
        - Why is it correct? Well, let's consider the spanning tree (1) and the set of S-edges (2). Let's add
        one edge in (3) into tree (1). That edge must create a cycle in the tree (1), and that cycle contains
        at least one M-edge, so in order to make that cycle disappears, we simply remove that M-edge. In other
        words, we remove 1 M-edge to add 1 S-edge. When there are (n-1)/2 S-edges, there would be exactly the
        same number of M-edge. It's correct till the end of the algorithm.
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
const int MAXN = 1010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, lab[MAXN];
vector<III> M, S;
vector<int> res;
vector<II> listEdges;

void noResult() {
    cout << -1;
    exit(0);
}

int getRoot(int u) {
    while (lab[u] > 0) u = lab[u];
    return u;
}

void unionFind(int u, int v) {
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        char ch;
        cin >> u >> v >> ch;
        if (u != v) {
            if (ch == 'M') M.push_back({{u, v}, i});
            else S.push_back({{u, v}, i});
        }
    }
    if (n % 2 == 0) noResult();
    
    FOR(i,1,n) lab[i] = -1;
    int cnt = n;
    FOR(i,0,SZ(M)-1) {
        III p = M[i];
        int u = p.FI.FI, v = p.FI.SE;
        u = getRoot(u);
        v = getRoot(v);
        if (u != v) {
            unionFind(u, v);
            cnt--;
        }
    }
    FOR(i,0,SZ(S)-1) {
        III p = S[i];
        int u = p.FI.FI, v = p.FI.SE;
        u = getRoot(u);
        v = getRoot(v);
        if (u != v) {
            unionFind(u, v);
            res.push_back(p.SE);
            listEdges.push_back(p.FI);
            cnt--;
            if (SZ(res) == (n-1) / 2) break;
        }
    }
    if (cnt > 1) noResult();

    FOR(i,1,n) lab[i] = -1;
    cnt = n;
    FOR(i,0,SZ(listEdges)-1) {
        int u = listEdges[i].FI, v = listEdges[i].SE;
        u = getRoot(u);
        v = getRoot(v);
        unionFind(u, v);
        cnt--;
    }

    if (SZ(res) < (n-1) / 2) {
        FOR(i,0,SZ(S)-1) {
            III p = S[i];
            int u = p.FI.FI, v = p.FI.SE;
            u = getRoot(u);
            v = getRoot(v);
            if (u != v) {
                unionFind(u, v);
                res.push_back(p.SE);
                cnt--;
                if (SZ(res) == (n-1) / 2) break;
            }
        }
    }

    if (SZ(res) < (n-1) / 2) noResult();

    FOR(i,0,SZ(M)-1) {
        III p = M[i];
        int u = p.FI.FI, v = p.FI.SE;
        u = getRoot(u);
        v = getRoot(v);
        if (u != v) {
            unionFind(u, v);
            res.push_back(p.SE);
            cnt--;
        }
    }

    if (cnt > 1) noResult();

    cout << SZ(res) << "\n";
    FOR(i,0,SZ(res)-1) cout << res[i] << ' ';
    return 0;
}
