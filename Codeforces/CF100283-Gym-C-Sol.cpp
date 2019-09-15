/*
    Author: Nguyen Tan Bao
    Status: Resolve after reading editorial
    Idea: https://codeforces.com/blog/entry/9571
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
const int MAXN = 110;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

int t, n, m, s, x, y;
ll a[MAXN*2][MAXN*2], b[MAXN*2][MAXN*2], sum[MAXN*2][MAXN*2];

int toRow(int i, int j) {
    return i + j;
}

int toCol(int i, int j) {
    return i - j + m;
}

ll add(ll a, ll b) {
    return (a + b) % MODBASE;
}

ll sub(ll a, ll b) {
    return (a - b + MODBASE) % MODBASE;
}

void init() {
    cin >> n >> m >> s >> x >> y;
    FOR(i,1,n+m) FOR(j,1,n+m) a[i][j] = 0;
    FOR(i,1,n)
        FOR(j,1,m) {
            int x;
            cin >> x;
            a[toRow(i,j)][toCol(i,j)] = x;
        }
}

ll getSum(int u, int v, int x, int y) {
    // (u, v) top left
    // (x, y) bottom right
    u = max(u, 1);
    v = max(v, 1);
    x = min(x, n+m);
    y = min(y, n+m);

    if (u > x || v > y) return 0;
    return add(sub(sub(sum[x][y], sum[u-1][y]), sum[x][v-1]), sum[u-1][v-1]);
}

void solve() {
    FOR(k,1,s-1) {
        FOR(i,1,n+m) FOR(j,1,n+m) b[i][j] = 0;
        FOR(i,1,n+m) FOR(j,1,n+m) sum[i][j] = add(sub(add(sum[i-1][j], sum[i][j-1]), sum[i-1][j-1]), a[i][j]);

        FOR(i,1,n)
            FOR(j,1,m) b[toRow(i,j)][toCol(i,j)] = getSum(toRow(i-k, j), toCol(i-k, j), toRow(i+k, j), toCol(i+k, j));

        FOR(i,1,n+m)
            FOR(j,1,n+m) a[i][j] = b[i][j];
    }
    cout << a[toRow(x,y)][toCol(x,y)] << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("treasures.in", "r", stdin);
    cin >> t;
    FOR(o,1,t) {
        cout << "Case " << o << ": ";
        init();
        solve();
    }
    return 0;
}
