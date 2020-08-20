/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The idea is quite simple, for each edge, we remove it, the tree is divided to 2 smaller
        ones. We then try to connect 2 largest uninfected components of those 2 smaller trees.
        One thing to note is that there may be a number of largest uninfected components in one tree.
        For example, there are 2 separated components with 5 persons in each components. We have to
        include all of them into the result.
        - For now, when talking about a component, we understand it as an uninfected component.
        - Let's define info[u] containing information of subtree of u (rooted at 1). It has the 
        following properties:
            + Max: size of the largest component.
            + Num: number of nodes in such components (maybe larger than Max if we have multiple of 
            such components)
            + Comp: is 0 if node u is infected, otherwise it would be the size of the component with
            u in it.
            + NumOfNode: number of nodes in the subtree of u
            + ok: is 0 if node u is infected, otherwise it is 1.
        - We also need to calculate allPairs which is number of pairs of reachable uninfected nodes.
        It can be retrieved easily using dfs (dfs0 function)
        - Use dfs function to initialize info[u] (1 <= u <= n)
        - merge function is used to merge info of u and v but not to update Max with Comp, finalize 
        function will do it.
        - Now we use dfs2 to consider each edge (u, v), one tree would be info[v], another tree would
        be the combination of "above", info[w] (w not v), and node u (1). "above" is the tree containing
        p (parent of u) when we remove edge (p, u). The combination (1) can be used as "above" when we
        dfs2(v). 
        - So we have 2 tree a and b, how can we find Max number of pairs and number of ways to get 
        this? First, we remove number of pairs of a.Comp + b.Comp from allPairs, then we add pairs of
        a.Comp and pairs of b.Comp to it to get the number of pairs after breaking edge (u, v). Now
        we remove pairs of a.Max and pairs of b.Max and create new edge to connect 2 Max together by
        adding pairs of a.Max + b.Max. What about the number of ways? It would be a.Num * b.Num if
        both Max > 0, otherwise it is a.NumOfNode * b.NumOfNode, obviously.
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

struct NodeInfo {
    int Max, Num, Comp, NumOfNode, ok;
    NodeInfo(int Max = 0, int Num = 0, int Comp = 0, int NumOfNode = 0, int ok = 0) : Max(Max), Num(Num), Comp(Comp), NumOfNode(NumOfNode), ok(ok) {}
};

int n, k, e[MAXN];
bool visited[MAXN];
ll Max, ways, allPairs, cmp;
NodeInfo info[MAXN], r[MAXN], ab[MAXN];
vector<int> a[MAXN], b[MAXN];
string s;

void input() {
    ll A, B, C;
    cin >> n >> k;
    cin >> s;
    s = " " + s;

    FOR(i,2,k+1) cin >> e[i];
    cin >> A >> B >> C;
    FOR(i,k+2,n) e[i] = (A * e[i-2] + B * e[i-1] + C) % (i-1) + 1;
}

void init() {
    Max = ways = allPairs = 0;
    FOR(i,1,n) {
        a[i].clear();
        b[i].clear();
        visited[i] = false;
    }
}

NodeInfo merge(NodeInfo u, NodeInfo v) {
    if (u.Max < v.Max) {
        u.Max = v.Max;
        u.Num = v.Num;
    } else if (u.Max == v.Max && v.Max) u.Num += v.Num;
    if (u.ok) u.Comp += v.Comp;
    return u;
}

NodeInfo finalize(NodeInfo u) {
    if (u.Max < u.Comp) {
        u.Max = u.Comp;
        u.Num = u.Comp;
    } else if (u.Max == u.Comp && u.Comp) u.Num += u.Comp;
    return u;
}

void dfs0(int u) {
    visited[u] = true;
    cmp++;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (!visited[v] && s[v] == '*') dfs0(v);
    }
}

void dfs(int u, int p) {
    info[u].Max = info[u].Num = 0;
    info[u].Comp = info[u].ok = (s[u] == '*');
    info[u].NumOfNode = 1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        b[u].push_back(v);
        dfs(v, u);
        info[u].NumOfNode += info[v].NumOfNode;
        info[u] = merge(info[u], info[v]);
    }
    info[u] = finalize(info[u]);
}

void compare(ll a, ll b) {
    if (a > Max) {
        Max = a;
        ways = b;
    } else if (a == Max) ways += b;
}

ll pairs(ll a) {
    return a * (a - 1) / 2;
}

void getRes(NodeInfo a, NodeInfo b) {
    ll w = allPairs - pairs(a.Comp + b.Comp);
    w += pairs(a.Comp) + pairs(b.Comp);
    w -= pairs(a.Max) + pairs(b.Max);
    w += pairs(a.Max + b.Max);

    if (a.Max == 0 || b.Max == 0) compare(w, (ll) a.NumOfNode * b.NumOfNode);
    else compare(w, (ll) a.Num * b.Num);
}

void dfs2(int u, NodeInfo above) {
    int x = (s[u] == '*');
    r[SZ(b[u])] = NodeInfo(0, 0, x, 1, x);
    FORE(i,SZ(b[u])-1,0) {
        int v = b[u][i];
        r[i] = merge(r[i+1], info[v]);
    }
    NodeInfo now = NodeInfo(0, 0, 0, 0, x);
    FOR(i,0,SZ(b[u])-1) {
        int v = b[u][i];

        NodeInfo cur = finalize(merge(merge(now, r[i+1]), above));
        cur.NumOfNode = n - info[v].NumOfNode;
        getRes(cur, info[v]);
        ab[v] = cur;
        now = merge(now, info[v]);
    }
    FOR(i,0,SZ(b[u])-1) {
        int v = b[u][i];
        dfs2(v, ab[v]);
    }
}

void handle() {
    FOR(i,2,n) {
        a[e[i]].push_back(i);
        a[i].push_back(e[i]);
    }
    FOR(i,1,n)
        if (!visited[i] && s[i] == '*') {
            cmp = 0;
            dfs0(i);
            allPairs += pairs(cmp);
        }
    dfs(1, 0);
    dfs2(1, NodeInfo());
    cout << Max << ' ' << ways << "\n";
}

void solve() {
    input();
    init();
    handle();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        solve();
    }
    return 0;
}
