/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Understand correctly the statement:
            + Given a starting node s and an ending node f and another node r. For all shortest
            paths from s to f, find the largest distance from r to one of the path.
        - Let x be the result here. If we check a "largest" distance d < x, the caravan can 
        still go from s to f using one of the shortest path so d is not really the largest distance
        here. Otherwise, if the largest distance is d >= x, the caravan cannot go from s to f
        normally (using one of the shortest path, now it has to go using another longer path or
        there is no way to go at all).
        - Using the above observation, we can use binary search to check. In each check(len), we try
        to go from s to f without going through nodes that have distance to r <= len and see
        if we can still go to f with the shortest path's length or not.
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

int n, m, s, f, r, d[2][MAXN], D[MAXN];
vector<int> a[MAXN];

void bfs(int t, int root) {
    FOR(i,1,n) d[t][i] = 1000000000;
    queue<int> q;
    q.push(root);
    d[t][root] = 0;
    while (SZ(q)) {
        int u = q.front(); q.pop();
        for (int v : a[u])
            if (d[t][v] > d[t][u] + 1) {
                d[t][v] = d[t][u] + 1;
                q.push(v);
            } 
    }
}

bool check(int len, int st) {
    if (d[1][s] <= len) return true;
    FOR(i,1,n) D[i] = 1000000000;
    queue<int> q;
    q.push(s);
    D[s] = 0;
    while (SZ(q)) {
        int u = q.front(); q.pop();
        for (int v : a[u]) {
            if (d[1][v] <= len) continue;
            if (D[v] > D[u] + 1) {
                D[v] = D[u] + 1;
                q.push(v);
            } 
        }
    }
    return D[f] > st;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    cin >> s >> f >> r;
    bfs(0, s);
    bfs(1, r);
    int len = d[0][f];
    int dau = 0, cuoi = n;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (check(mid, len)) cuoi = mid-1;
        else dau = mid+1;
    }
    cout << dau;
    return 0;
}
