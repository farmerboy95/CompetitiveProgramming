// https://stackoverflow.com/questions/30486784/how-to-find-if-a-graph-is-bipartite
#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define Y second
#define ld double
#define EPS 1e-9
#define all(a) a.begin(),a.end()
#define sz(a) int((a).size())
#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define what_is(x) cout << #x << " is " << x << endl;
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
typedef pair<int, int> II;
typedef pair<ll, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

int n, m, mark[100010];
vector<int> a[100010], res[3];

int dfs(int u, int color) {
    mark[u] = color;
    res[color].emplace_back(u);
    FOR(i,0,sz(a[u])-1) {
        int v = a[u][i];
        if (!mark[v] && dfs(v, 3-color)) return 1;
        if (mark[v] != 3-color) return 1;
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }
    FOR(i,1,n)
        if (!mark[i]) {
            if (sz(a[i]) == 0) continue;
            if (dfs(i, 1)) {
                cout << -1;
                return 0;
            }
        }
    FOR(i,1,2) {
        cout << sz(res[i]) << "\n";
        FOR(j,0,sz(res[i])-1) cout << res[i][j] << ' ';
        cout << "\n";
    }
    return 0; 
}
