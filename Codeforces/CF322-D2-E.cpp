/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: https://codeforces.com/blog/entry/8192 - up-down construction
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
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, d[MAXN], trace[MAXN], bfsTime, visited[MAXN];
vector<int> a[MAXN], b;
char res[MAXN];
queue<int> q;

int bfs(int u, int t) {
    // to save time to init, we use "t" as a value for "visited" array, 
    // so that we can check if a node is visited by comparing visited[u] with t
    visited[u] = t;
    d[u] = 0;
    q.push(u);
    int longest = 0, node = u;
    while (!q.empty()) {
        int r = q.front();
        q.pop();
        FOR(i,0,SZ(a[r])-1) {
            int v = a[r][i];
            if (visited[v] == t) continue;
            if (res[v] != ' ') continue;
            d[v] = d[r] + 1;
            visited[v] = t;
            // find the farthest node from u simutaneously
            if (d[v] > longest) {
                longest = d[v];
                node = v;
            }
            trace[v] = r;
            q.push(v);
        }
    }
    // return the farthest node
    return node;
}

void solve(int u, char now) {
    if (res[u] != ' ') return;

    // bfs from u to find the farthest node from u (r)
    int r = bfs(u, ++bfsTime);
    // bfs from r to find the farthest node from r (p)
    int p = bfs(r, ++bfsTime);

    // get all nodes in the path from r to p
    b.clear();
    while (p != r) {
        b.emplace_back(p);
        p = trace[p];
    }
    b.emplace_back(r);

    // chosen is the centroid of the subtree of u
    int chosen = b[SZ(b)/2];

    res[chosen] = now;
    FOR(i,0,SZ(a[chosen])-1) {
        int v = a[chosen][i];
        // go to the next subtree
        solve(v, now+1);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }
    FOR(i,1,n) res[i] = ' ';
    solve(1, 'A');

    FOR(i,1,n) cout << res[i] << ' ';
    return 0;
}
