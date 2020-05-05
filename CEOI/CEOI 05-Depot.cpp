/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2005/soldepot.pdf
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
const int MAXN = 410;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, itr[MAXN*2];
vector<int> pos[MAXN][MAXN];
vector<II> a[MAXN*2], res;
vector<int> edges;

void euler(int u) {
    for (; itr[u] < SZ(a[u]); ) {
        int v = a[u][itr[u]].FI;
        int p = a[u][itr[u]].SE;
        itr[u]++;
        euler(v);
        if (p != -1) edges.push_back(p);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n)
        FOR(j,1,m) {
            int x;
            cin >> x;
            // for each value and group of m containers, we store positions in pos[x][i]
            pos[x][i].push_back((i-1) * m + j);
        }
    FOR(j,1,m)
        FOR(i,1,n) {
            // if there is more than one value in a group, create a one-way edge connecting group i and value j
            FOR(k,1,SZ(pos[j][i])-1) a[i].push_back(II(j+n, pos[j][i][k]));
            // if there is no such value in a group, create a one-way edge connecting value j and group i
            if (!SZ(pos[j][i])) a[j+n].push_back(II(i, -1));
        }
    
    FOR(i,1,n+m) {
        // get a component's Eulerian circuit and put result into "res" array, then reset the "edges" array
        euler(i);
        if (SZ(edges)) {
            // remember to put the first one to the free position first
            res.push_back(II(edges[0], n*m+1));
            FOR(j,1,SZ(edges)-1) res.push_back(II(edges[j], edges[j-1]));
            res.push_back(II(n*m+1, edges[SZ(edges)-1]));
            edges.clear();
        }
    }
    cout << SZ(res) << "\n";
    for (II r : res) cout << r.FI << ' ' << r.SE << "\n";
    return 0;
}
