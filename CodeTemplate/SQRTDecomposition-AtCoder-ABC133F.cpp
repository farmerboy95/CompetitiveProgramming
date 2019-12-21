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
const int MAXN = 100010;
const int MAXM = 1000010;
const int MAXK = 510;
const int MAXQ = 200010;

struct EdgeData {
    int des, col, len;
    EdgeData(int des = 0, int col = 0, int len = 0) : des(des), col(col), len(len) {}
};

int n, m, d[MAXN], dist[MAXN], parent[MAXN][20];
EdgeData par[MAXN];
vector<EdgeData> a[MAXN];
bool special[MAXN], checked[MAXN];
vector<map<int, II> > colorData;
map<int, II> curColorData;

void dfs(int u, int p) {
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].des;
        int len = a[u][i].len;
        if (v == p) continue;
        d[v] = d[u]+1;
        parent[v][0] = u;
        par[v] = a[u][i];
        dist[v] = dist[u] + len;
        dfs(v, u);
    }
}

void dfs2(int u, int p) {
    if (special[u]) colorData[u] = curColorData;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i].des;
        int col = a[u][i].col;
        int len = a[u][i].len;
        if (v == p) continue;
        if (!curColorData.count(col)) curColorData[col] = II(0,0);
        curColorData[col].FI++;
        curColorData[col].SE += len;
        dfs2(v, u);
        curColorData[col].FI--;
        curColorData[col].SE -= len;
        if (curColorData[col].FI == 0) curColorData.erase(col);
    }
}

int lca(int u, int v) {
    if (d[v] < d[u]) FORE(i,17,0) if (d[parent[u][i]] >= d[v]) u = parent[u][i];
    if (d[u] < d[v]) FORE(i,17,0) if (d[parent[v][i]] >= d[u]) v = parent[v][i];
    FORE(i,17,0) if (parent[u][i] != parent[v][i]) { u = parent[u][i]; v = parent[v][i]; }
    while (u != v) { u = parent[u][0]; v = parent[v][0]; }
    return u;
}

II getData(int u, int color) {
    if (special[u]) {
        if (!colorData[u].count(color)) {
            return II(0, 0);
        } else {
            return colorData[u][color];
        }
    }

    II prev = getData(parent[u][0], color);
    EdgeData p = par[u];
    if (p.col == color) {
        prev.FI++;
        prev.SE += p.len;
    }
    return prev;
}

int rootDist(int u, II data, int rep) {
    return dist[u] - data.SE + rep * data.FI;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n-1) {
        int u, v, c, l;
        cin >> u >> v >> c >> l;
        a[u].emplace_back(EdgeData(v, c, l));
        a[v].emplace_back(EdgeData(u, c, l));
    }
    parent[1][0] = 1;
    dfs(1, 0);
    FOR(j,1,17)
        FOR(i,1,n) parent[i][j] = parent[parent[i][j-1]][j-1];
    priority_queue<II> h;
    FOR(i,1,n) h.push(II(d[i], i));
    special[1] = true;
    checked[1] = true;
    while (!h.empty()) {
        int u = h.top().SE;
        h.pop();
        if (checked[u]) continue;
        FOR(i,1,350) {
            u = parent[u][0];
            if (special[u]) break;
            checked[u] = true;
        }
        special[u] = true;
    }
    FOR(i,0,n) {
        map<int, II> blank;
        colorData.emplace_back(blank);
    }
    dfs2(1,0);
    FOR(i,1,m) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        int g = lca(u, v);
        cout << rootDist(u, getData(u, x), y) + rootDist(v, getData(v, x), y) - 2 * rootDist(g, getData(g, x), y) << "\n";
    }
    return 0;
}
