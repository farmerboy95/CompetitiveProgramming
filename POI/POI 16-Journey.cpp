/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Approach:
        - At first I thought about some idea:
            + cycle cannot contain a bridge => remove all bridges
            + path in cycle cannot go through an articulation point => break the graph to smaller piece by articulation point
        - I got stuck because I had no idea what a biconnected component is, so I implemented it in my way and I definitely got WA.
        - I also missed the case that chosen graph should be an "onion" graph (according to the editorial)
        - After reading editorial and code, I knew how to implement and got AC.
    Idea: 
        - More or less like this code: https://github.com/stefdasca/CompetitiveProgramming/blob/master/POI/POI%2016-Journey.cpp

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
typedef pair<ll, ll> II;
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
const int MAXN = 500010;
const int MAXM = 1000010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m, dfsNum, num[MAXN], low[MAXN], d[MAXN], len;
ll cnt;
vector<int> a[MAXN], b[MAXN];
stack<II> s;
vector<II> edges;
set<int> group;

// bfs to check whether this biconnected component is a onion graph or not
bool bfs(int st, int en) {
    queue<int> q;
    q.push(st);
    d[st] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        FOR(i,0,SZ(b[u])-1) {
            int v = b[u][i];
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                if (en != v) q.push(v);
            }
            else {
                if (v == en) {
                    if (d[v] != d[u] + 1) return false;
                }
            }
        }
    }
    return true;
}

bool check() {
    // bridges => return
    if (SZ(edges) == 1) return true;
    FOR(i,0,SZ(edges)-1) {
        group.insert(edges[i].FI);
        group.insert(edges[i].SE);
    }

    FOR(i,0,SZ(edges)-1) {
        int u = edges[i].FI, v = edges[i].SE;
        b[u].emplace_back(v);
        b[v].emplace_back(u);
        d[u]++; d[v]++;
    }

    // onion graph has exactly 2 vertices which have degree > 2
    vector<int> not2;
    FORALL(it, group) {
        int u = *it;
        if (d[u] != 2) not2.emplace_back(u);
    }

    // normal cycle
    if (SZ(not2) == 0) {
        if (!len) len = SZ(group);
        else if (len != SZ(group)) return false;
        cnt = (cnt+1) % MODBASE;
    }
    else if (SZ(not2) != 2) return false;
    else {
        // check if this component is an onion graph
        int st = not2[0], en = not2[1];
        if (d[st] != d[en]) return false;
        FORALL(it, group) {
            int u = *it;
            d[u] = -1;
        }
        if (!bfs(st, en)) return false;
        int k = SZ(b[st]);
        int l = d[en] * 2;
        if (!len) len = l;
        else if (len != l) return false;
        cnt = (cnt + (ll) k * (k - 1) / 2) % MODBASE;
    }
    return true;
}

void clean() {
    FOR(i,0,SZ(edges)-1) {
        int u = edges[i].FI, v = edges[i].SE;
        b[u].clear(); b[v].clear();
        d[u] = d[v] = 0;
    }
    edges.clear();
    group.clear();
}

// find biconnected components
bool dfs(int u, int p) {
    num[u] = low[u] = ++dfsNum;
    bool co = true;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        if (num[v] == 0) {
            s.push(II(u, v));
            co = dfs(v, u);
            if (!co) return false;
            low[u] = min(low[u], low[v]);
            if (low[v] >= num[u]) {
                II r;
                do {
                    r = s.top();
                    s.pop();
                    edges.emplace_back(r);
                } while (r != II(u, v) && r != II(v, u));
                co = check();
                if (!co) return false;
                clean();
            }
        }
        else {
            // back edge
            if (num[v] < num[u]) {
                s.push(II(u, v));
            }
            low[u] = min(low[u], num[v]);
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }
    // if graph is a tree => no cycle
    if (n == m+1) {
        cout << "BRAK";
        return 0;
    }
    bool exist = dfs(1, 0);
    if (exist) {
        cout << "TAK\n";
        cout << len << ' ' << cnt * len * 2 % MODBASE;
    }
    else cout << "NIE";
    return 0;
}
