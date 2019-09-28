/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Find a strongly connected component (has more than 1 vertex) of the graph (print -1 if there is no such component)
        - Use a simple DFS to find a cycle in that strongly connected component
        - For each directed edge in the graph that contains all vertices of the cycle:
            + If that edge is on border of the cycle and has the same direction of cycle, ignore it
            + Otherwise, that cycle would have a child cycle inside, get that child cycle and consider edges in new cycle again
            until it has no child cycle.
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
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

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 1010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m, low[MAXN], num[MAXN], dfsNum, sccCnt;
vector<II> edges;
vector<int> a[MAXN], cmp[MAXN];
bool visited[MAXN];
stack<int> s;
set<int> se;

// find strongly connected components
void scc(int u) {
    low[u] = num[u] = ++dfsNum;
    s.push(u);
    visited[u] = true;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (num[v] == -1) scc(v);
        if (visited[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        int k = -1;
        sccCnt++;
        int dem = 0;
        do {
            k = s.top();
            cmp[sccCnt].emplace_back(k);
            s.pop();
            visited[k] = false;
            dem++;
        } while (k != u);
    }
}

bool found = false, inside = true;
int root = -1;
vector<int> b, c;

void dfs(int u) {
    visited[u] = true;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (!visited[v]) {
            dfs(v);
            if (found) {
                if (inside) b.emplace_back(u);
                if (u == root) inside = false;
                return;
            }
        }
        else {
            found = true;
            root = v;
            b.emplace_back(u);
            return;
        }
    }
}

void solve(int compIndex) {
    FOR(i,1,n) a[i].clear();

    FOR(i,0,SZ(cmp[compIndex])-1) {
        int u = cmp[compIndex][i];
        se.insert(u);
        visited[u] = false;
    }

    FOR(i,0,SZ(edges)-1) 
        if (se.count(edges[i].FI) && se.count(edges[i].SE)) a[edges[i].FI].emplace_back(edges[i].SE);
    
    // find a cycle in this component
    dfs(cmp[compIndex][0]);
    reverse(ALL(b));

    while (SZ(edges) > 0) {
        se.clear();
        FOR(i,0,SZ(b)-1) {
            int u = b[i];
            se.insert(u);
        }

        while (SZ(edges) > 0) {
            II r = edges.back();
            edges.pop_back();
            if (!(se.count(r.FI) && se.count(r.SE))) continue;

            int u = r.FI, v = r.SE;
            int posU = -1, posV = -1;

            FOR(i,0,SZ(b)-1) {
                if (b[i] == u) posU = i;
                if (b[i] == v) posV = i;
            }

            // edge on border and has the same direction as cycle
            if ((posU + 1) % SZ(b) == posV) continue;

            // going to the small cycle
            c.clear();
            while (posV != posU) {
                c.emplace_back(b[posV]);
                posV = (posV + 1) % SZ(b);
            }
            c.emplace_back(b[posU]);

            b = c;
            break;
        }
    }

    cout << SZ(b) << "\n";
    FOR(i,0,SZ(b)-1) cout << b[i] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        edges.push_back(II(u, v));
        a[u].emplace_back(v);
    }
    FOR(i,1,n) num[i] = -1;
    FOR(i,1,n)
        if (num[i] == -1) scc(i);
    FOR(i,1,sccCnt) {
        if (SZ(cmp[i]) != 1) {
            // consider 1 strongly connected component
            solve(i);
            return 0;
        }
    }
    cout << -1;
    return 0;
}
