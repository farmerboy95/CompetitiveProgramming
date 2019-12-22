/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: More or less like https://codeforces.com/blog/entry/72212
        - Proof of tree convolution 
        https://drive.google.com/file/d/1nhL63QcjUiRm1pGGmzi1QHceKAGeBsRY/view
*/
 
#include "bits/stdc++.h"
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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 3010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Group {
    int win;
    ll diff;
    Group(int win = -1, ll diff = 0) : win(win), diff(diff) {}
    Group operator+(const Group &o) const {
        return Group(win + o.win, diff + o.diff);
    }
    Group operator+() const {
        return Group(win + (diff > 0));
    }
    bool operator<(const Group& o) const {
        return win < o.win || (win == o.win && diff < o.diff);
    }
};

int n, m;
vector<vector<Group> > dp;
vector<int> a[MAXN];

vector<Group> merge(vector<Group> &child, vector<Group> &par) {
    vector<Group> res(SZ(child) + SZ(par));
    FOR(i,0,SZ(child)-1)
        FOR(j,0,SZ(par)-1) {
            res[i+j] = max(res[i+j], child[i] + par[j]);
            res[i+j+1] = max(res[i+j+1], +child[i] + par[j]);
        }
    return res;
}

void dfs(int u, int p) {
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        dfs(v, u);
        dp[u] = merge(dp[v], dp[u]);
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        dp = vector<vector<Group> >(n+1, vector<Group>(1, Group(0)));
        FOR(i,1,n) {
            int x;
            cin >> x;
            dp[i][0].diff -= x;
        }
        FOR(i,1,n) {
            int x;
            cin >> x;
            dp[i][0].diff += x;
        }
        FOR(i,1,n) a[i].clear();
        FOR(i,1,n-1) {
            int u, v;
            cin >> u >> v;
            a[u].emplace_back(v);
            a[v].emplace_back(u);
        }
        dfs(1, 0);
        cout << (+dp[1][m-1]).win << "\n";
    }
    return 0;
}