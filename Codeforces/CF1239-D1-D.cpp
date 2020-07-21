/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's assume we have a graph that has n vertices and m edges (u -> v)
        - Let's assume that we choose judge x to be in the result. If there is and edge (x, y), we must choose
        judge y as well. That means, there is no path (x, y) where x is a judge and y is a cat.
        - It also means that if we have a number of strongly connected components (SCCs), vertices in one
        component will have the same state (to be a judge or to be a cat) => We should have more than 1 SCC.
        - Now let's print out the result. We should start in a component that has no in-degree, and make it
        cats' component. Why? Because that component may have out-degree. If we make it judges' component.
        The next component when going by the out-edge must be judges' component as well. Making this component
        as a cats' one and the remaining as judges' ones will make the result valid.
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
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int t, n, m, low[MAXN], num[MAXN], dfsNum, sccCnt, w[MAXN], z[MAXN];
stack<int> s;
vector<II> edges;
vector<int> a[MAXN];
bool visited[MAXN];

void scc(int u) {
    low[u] = num[u] = ++dfsNum;
    s.push(u);
    visited[u] = true;
    for (int v : a[u]) {
        if (num[v] == -1) scc(v);
        if (visited[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        int k = -1;
        sccCnt++;
        do {
            k = s.top();
            s.pop();
            w[k] = sccCnt;
            visited[k] = false;
        } while (k != u);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n >> m;
        edges.clear();
        sccCnt = 0;
        dfsNum = -1;
        FOR(i,1,n) {
            a[i].clear();
            low[i] = num[i] = -1; 
            visited[i] = w[i] = 0;
            z[i] = 0;
        }
        FOR(i,1,m) {
            int u, v;
            cin >> u >> v;
            if (u == v) continue;
            edges.push_back(II(u, v));
            a[u].push_back(v);
        }
        FOR(i,1,n)
            if (num[i] == -1) scc(i);
        
        // should have more than one SCC
        if (sccCnt == 1) {
            cout << "No\n";
            continue;
        }

        // if a component i has an in-degree, z[i] = 1
        for (II x : edges)
            if (w[x.FI] != w[x.SE]) z[w[x.SE]] = 1;
        
        // start at a component that has zero in-degree
        int st = 0;
        FOR(i,1,sccCnt)
            if (!z[i]) st = i;
        
        // assert for sure
        if (st == 0) {
            cout << "No\n";
            continue;
        }

        int cats = 0;
        FOR(i,1,n)
            if (w[i] == st) cats++;
        cout << "Yes\n" << n-cats << ' ' << cats << "\n";
        FOR(i,1,n)
            if (w[i] != st) cout << i << ' ';
        cout << endl;
        FOR(i,1,n)
            if (w[i] == st) cout << i << ' ';
        cout << endl;
    }
    return 0;
}

