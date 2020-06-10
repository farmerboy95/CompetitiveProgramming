/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let shortest[u][v] is the shortest path from u to v. Consider the largest shortest[u][v].
        Let it be p. If p == 1, there would be no edge added and we print out the result.
        - But if p > 1, there are 2 following cases:
            + if p is even, p will become p/2 (as we can directly go 2 steps from u and so on)
            + if p is odd, p will become p/2 + 1 (same as above but one of the step would be 1)
        - So we can build kq[i] which is the number of days needed when the largest shortest path
        is i
        - But how can we find largest shortest path of the graph?
        - One can easily find out a naive solution in which he would bfs from each node, but it 
        takes him too long time => TLE.
        - We notice that if the exact result is X, we can print out X-1, X or X+1. This is the key
        point. Now we may bfs from an arbitrary node (node 1) and get the longest shortest path r from 1.
        But what does it mean? The key observation is that r >= p/2 + p%2 (the equal sign happens when
        we bfs from the middle point on the path). And kq[r] >= X-1, which is acceptable.
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
const int MAXN = 21010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int t, n, m, d[MAXN], kq[MAXN];
vector<int> a[MAXN];

int bfs() {
    queue<int> q;
    MS(d, -1);
    d[1] = 0;
    q.push(1);
    while (SZ(q)) {
        int u = q.front(); q.pop();
        FOR(i,0,SZ(a[u])-1) {
            int v = a[u][i];
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    int res = 0;
    FOR(i,1,n) res = max(res, d[i]);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("amici2.in", "r", stdin);
    freopen("amici2.out", "w", stdout);
    cin >> t;
    FOR(i,1,21000)
        if (i % 2) kq[i] = kq[i / 2 + 1] + 1;
        else kq[i] = kq[i / 2] + 1;
    while (t--) {
        cin >> n >> m;
        FOR(i,1,n) a[i].clear();
        FOR(i,1,m) {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }
        int tempLongest = bfs();
        cout << kq[tempLongest] << "\n";
    }
    return 0;
}
