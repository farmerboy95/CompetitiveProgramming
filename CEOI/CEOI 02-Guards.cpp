/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2002/guards-sol.pdf
        - Create bipartite graph and simply run the finding augmenting path algorithm
        - Specific comments in code
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
const int MAXN = 210;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, c[MAXN][MAXN], match[MAXN*MAXN];
bool seen[MAXN*MAXN];
vector<int> a[MAXN*MAXN];
II b[MAXN][MAXN];
map<II, II> ma;

bool bipartiteMatching(int u) {
    if (seen[u]) return false;
    seen[u] = true;
    for (int v : a[u])
        if (match[v] == -1 || bipartiteMatching(match[v])) {
            match[v] = u;
            return true;
        }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n)
        FOR(j,1,m) cin >> c[i][j];

    // intially, there are n row segments and m column segments
    int rowCnt = n, colCnt = m;
    FOR(i,1,n)
        FOR(j,1,m) {
            if (c[i][j] == 0) {
                // if c[i][j] is free, get the current row segment index and column segment index
                // create edge from row-index to column-index in bipartite graph
                int x, y;
                if (j == 1) x = i;
                else x = b[i][j-1].FI;
                if (i == 1) y = j;
                else y = b[i-1][j].SE;
                b[i][j] = II(x, y);
                a[x].push_back(y);
            }
            else if (c[i][j] == 1) {
                // if c[i][j] is a pit, do as above but we don't create edge as there is no guard
                // on this cell
                int x, y;
                if (j == 1) x = i;
                else x = b[i][j-1].FI;
                if (i == 1) y = j;
                else y = b[i-1][j].SE;
                b[i][j] = II(x, y);
            }
            // a wall? we see new segments, just increase both
            else b[i][j] = II(++rowCnt, ++colCnt);
            // store the edge in the map for tracing the result
            ma[b[i][j]] = II(i, j);
        }
    
    // this part is just the same as the maximum bipartite matching algorithm
    FOR(i,1,colCnt) match[i] = -1;
    int res = 0;
    FOR(i,1,rowCnt) {
        FOR(j,1,rowCnt) seen[j] = false;
        res += bipartiteMatching(i);
    }

    // then trace the result from the map above based on the matching
    cout << res << "\n";
    FOR(i,1,colCnt)
        if (match[i] != -1) {
            II r = ma[II(match[i], i)];
            cout << r.FI << ' ' << r.SE << "\n";
        }
    return 0;
}
