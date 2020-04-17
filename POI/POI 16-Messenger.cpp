/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let all[u][v][d] is number of paths from u to v, length of path is d.
        - Let all2[u][v][d] is number of paths from u to v, length of path is d but the path cannot
        go through u twice.
        - Let all3[u][v][d] is number of paths from v to u, length of path is d but the path cannot
        go through u twice, it's basically all2 in the reverse graph.
        - All of the above arrays can be calculated in O(n^3 * d)

        - Let res[u][v][d] is the number of paths from u to v, length of path is d, not going through
        u, v twice (the result)
        - We are going to pre-calculate all res[u][v][d] and simply print result for each query.
        - We define f[u][v][d] is the number of paths from u to u but not going through v, length of 
        path is d.
        - f[u][v][d] = all[u][u][d] - (all3[v][u][k] * all[v][u][d-k]) (0 < k < d) (O(n^2 * d^2))
          (all u -> u but no v) = (all u -> u) - ((u -> first v) * (all v -> u))
        - So res[u][v][d] = all2[u][v][d] - (res[u][v][k] * f[v][u][d-k]) (0 < k < d) (O(n^2 * d^2))
          (only u -> only v) = (only u -> v) - ((only u -> only v) * (all v -> v but no u))
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
const int MAXN = 110;
const int MAXM = 55;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;
ll MOD, res[MAXN][MAXN][MAXM], all2[MAXN][MAXN][MAXM], all3[MAXN][MAXN][MAXM], f[MAXN][MAXN][MAXM], all[MAXN][MAXN][MAXM];
vector<int> a[MAXN], b[MAXN];

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

// O(n^2 * d)
void initAll2(int st) {
    all2[st][st][0] = 1;
    FOR(len,0,49)
        FOR(u,1,n)
            FOR(i,0,SZ(a[u])-1) {
                int v = a[u][i];
                if (v == st) continue;
                all2[st][v][len+1] = add(all2[st][v][len+1], all2[st][u][len]);
            }
}

void initAll3(int st) {
    all3[st][st][0] = 1;
    FOR(len,0,49)
        FOR(u,1,n)
            FOR(i,0,SZ(b[u])-1) {
                int v = b[u][i];
                if (v == st) continue;
                all3[st][v][len+1] = add(all3[st][v][len+1], all3[st][u][len]);
            }
}

void initAll(int st) {
    all[st][st][0] = 1;
    FOR(len,0,49)
        FOR(u,1,n)
            FOR(i,0,SZ(a[u])-1) {
                int v = a[u][i];
                all[st][v][len+1] = add(all[st][v][len+1], all[st][u][len]);
            }
}

void init() {
    // O(n^3 * d)
    FOR(i,1,n) {
        initAll(i);
        initAll2(i);
        initAll3(i);
    }
    FOR(d,1,50) {
        FOR(u,1,n)
            FOR(v,1,n) {
                if (u == v) continue;
                res[u][v][d] = all2[u][v][d];
                FOR(k,1,d-1) res[u][v][d] = sub(res[u][v][d], mul(res[u][v][k], f[v][u][d-k]));
                f[u][v][d] = all[u][u][d];
                FOR(k,1,d-1) f[u][v][d] = sub(f[u][v][d], mul(all3[v][u][k], all[v][u][d-k]));
            }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> MOD;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        // reverse graph
        b[v].push_back(u);
    }

    init();
    int q;
    cin >> q;
    while (q--) {
        int u, v, c;
        cin >> u >> v >> c;
        cout << res[u][v][c] << "\n";
    }
    return 0;
}
