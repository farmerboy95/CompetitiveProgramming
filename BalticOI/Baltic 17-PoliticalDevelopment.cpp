/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Create a graph that has edges connecting u and v that u, v are policians who disagree with
        each other.
        - As the statement declares that for any non-empty group of points, there is always at least
        one point that its number of adjacent points is smaller than K.
        - So let's say that group of points is the whole graph, there is at least one point satisties
        the above condition, we can use the point that has smallest number of adjacent points. We can 
        get its adjacent points and try to find a clique that contains itself and a subset of its 
        adjacent points. It would take about O(2^K * K^2).
        - After finding a clique containing a specific point, we can remove it and repeat the above
        steps.
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

int n, k;
set<int> a[MAXN];
set<II> s;

bool check(vector<int> &e) {
    FOR(i,0,SZ(e)-1)
        FOR(j,0,i-1) {
            int x = e[i], y = e[j];
            if (!a[x].count(y)) return false;
        }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,0,n-1) {
        int p, x;
        cin >> p;
        FOR(j,0,p-1) {
            cin >> x;
            a[i].insert(x);
        }
    }
    // we maintain a set of points that are still in the graph
    FOR(i,0,n-1) s.insert(II(SZ(a[i]), i));
    int res = 1;
    while (SZ(s)) {
        // get the point u that has a smallest number of adjacent points
        II r = *s.begin();
        // remove u from the 
        s.erase(s.begin());
        int u = r.SE;
        // get a set of adjacent points of u
        vector<int> adj;
        FORALL(it, a[u]) adj.push_back(*it);
        int m = SZ(adj);
        // try to find a clique
        FOR(mask,1,(1<<m)-1) {
            vector<int> e;
            FOR(i,0,m-1)
                if (mask & (1<<i)) e.push_back(adj[i]);
            // check if e is a clique
            if (check(e)) res = max(res, SZ(e)+1);
        }

        // remove u
        FOR(i,0,m-1) {
            s.erase(s.lower_bound(II(SZ(a[adj[i]]), adj[i])));
            a[adj[i]].erase(u);
            s.insert(II(SZ(a[adj[i]]), adj[i]));
        }
    }
    cout << res;
    return 0;
}
