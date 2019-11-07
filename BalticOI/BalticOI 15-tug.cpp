/*
    Author: Nguyen Tan Bao
    Status: AC after reading sample code
    Idea: More or less like this submission https://github.com/nikolapesic2802/Programming-Practice/blob/master/Tug%20of%20War/main.cpp
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 60010;
const int MAXM = 600010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, k, deg[MAXN], diff;
multiset<II> a[MAXN];
queue<int> q;
bool visited[MAXN];
vector<int> dp;
bitset<MAXM> kns;

void dfs(int u) {
    visited[u] = true;
    if (SZ(a[u]) == 0) return;
    int v = a[u].begin()->FI;
    int c = a[u].begin()->SE;
    a[u].erase(a[u].begin());
    a[v].erase(a[v].find(II(u, c)));
    if (u < n) diff += c;
    else diff -= c;
    dfs(v);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,2*n) {
        int u, v, c;
        cin >> u >> v >> c;
        u--;
        v--; v += n;
        a[u].insert(II(v, c));
        a[v].insert(II(u, c));
        deg[u]++;
        deg[v]++;
    }
    FOR(i,0,2*n-1)
        if (deg[i] == 1) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        visited[u] = true;
        if (SZ(a[u]) == 0) continue;
        int v = a[u].begin()->FI;
        int c = a[u].begin()->SE;
        a[u].erase(a[u].begin());
        deg[u]--;
        deg[v]--;
        a[v].erase(a[v].find(II(u, c)));
        if (deg[v] == 1) q.push(v);
        if (u < n) diff += c;
        else diff -= c;
    }
    if (diff) {
        dp.push_back(abs(diff));
        diff = 0;
    }
    FOR(i,0,2*n-1) {
        if (!visited[i]) {
            if (deg[i] != 2) {
                cout << "NO";
                return 0;
            }
            dfs(i);
            if (diff) {
                dp.push_back(abs(diff));
                diff = 0;
            }
        }
    }
    sort(dp.rbegin(), dp.rend());
    if (SZ(dp) == 0) {
        cout << "YES\n";
        return 0;
    }

    kns[MAXM/2] = 1;
    FOR(i,0,SZ(dp)-1) kns = (kns<<dp[i]) | (kns>>dp[i]);

    bool res = false;
    FOR(i,MAXM/2,MAXM/2+k) res |= kns[i];
    if (res) cout << "YES";
    else cout << "NO";
    return 0;
}
