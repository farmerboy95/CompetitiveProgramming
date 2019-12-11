/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - As each person has less than 3 enemies, our job is to find number of odd simple cycles
        - Remember to remove 1 more person when we have odd number of persons left
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
typedef pair<ll, ll> II;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, res;
vector<int> a[MAXN], path;
int visit[MAXN];

void dfs(int u, int p) {
    visit[u] = 1;
    path.emplace_back(u);
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (visit[v] == 2 || v == p) continue;
        if (!visit[v]) dfs(v, u);
        else {
            int len = 1;
            FORE(j,SZ(path)-1,0) {
                if (path[j] == v) break;
                len++;
            }
            res += len % 2;
        }
    }
    visit[u] = 2;
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
    FOR(i,1,n)
        if (!visit[i]) dfs(i, 0);
    if ((n - res) % 2) res++;
    cout << res;
    return 0;
}
