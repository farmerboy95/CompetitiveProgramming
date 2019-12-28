/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Easily see that our good form contains cycles. More formally, for a permutation of n,
        |i...| |j...| |k...|, each region will be a cycle, with the max one first.
        - First we have dp[n], which is the number of good forms of length n.
        => dp[n] = f[i] * dp[n-i] (1 <= i <= n) (f[i] is the number of ways we create cycle with i nodes)
        - f[i] = (i - 2)! (i >= 2) or 1 (i == 1)
        (because the first one is i, we have i-1 connected components, we can permutate i-1 these components
        to get the number of ways but we need to fix one component => permutate i-2 components => (i-2)! )
        - Note that when x > 21, dp[x] > 10^18 so that we use a value > 10^18 to put into dp[x], we don't use
        it anyway, just to make sure that it's larger than 10^18

        - Then we solve this problem recursively:
            + Pick the region first
            + Print out the region (make sure that the region creates one cycle only), recalculate K at the same time.
            + Continue to solve the remaining nodes
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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 55;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int t, n, lab[MAXN], degIn[MAXN];
ll k, dp[MAXN], f[MAXN];

ll F(int u) {
    if (u <= 1) return 1;
    if (u > 21) return 2e18;
    if (f[u] != -1) return f[u];
    ll res = 1;
    FOR(i,1,u-2) res *= i;
    return f[u] = res; 
}

ll DP(int u) {
    if (u <= 21) return dp[u];
    return 2e18;
}

bool canConnect(int u, int v) {
    if (u == v) return false;
    if (degIn[v]) return false;
    if (lab[u] == lab[v]) return false;
    return true;
}

bool connect(int u, int v, int l, int r) {
    if (!canConnect(u, v)) return false;
    int p = lab[u];
    FOR(i,l,r)
        if (lab[i] == p) lab[i] = lab[v];
    degIn[v] = true;
    return true;
}

void build(int st, int n, ll x, ll &remain) {
    int en = st + n - 1;
    // the first one is max
    cout << en << ' ';
    if (n == 1) return;
    FOR(i,st,en) {
        lab[i] = i;
        degIn[i] = false;
    }
    connect(st, en, st, en);
    int numComp = n - 1;
    FOR(i,st+1,en)
        FOR(j,st,en) {
            if (i == en) {
                // if i == en, just choose a node that does not have in-degree
                if (!degIn[j]) {
                    cout << j << ' ';
                    break;
                }
                continue;
            }
            // make sure that we don't create the cycle till the last node
            if (canConnect(i, j)) {
                // x is the number of good forms after building this region
                if (x * F(numComp) < remain) {
                    remain -= x * F(numComp);
                    continue;
                }
                numComp--;
                connect(i, j, st, en);
                cout << j << ' ';
                break;
            }
        }
}

void solve(int n, ll remain, int st) {
    if (n <= 0) return;
    if (n == 1) {
        cout << st << ' ';
        return;
    }
    FOR(i,1,n)
        if (F(i) * DP(n-i) < remain) remain -= F(i) * DP(n-i);
        else {
            // pick region
            build(st, i, DP(n-i), remain);
            // continue to solve the remaining nodes
            solve(n-i, remain, st+i);
            break;
        }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    FOR(i,1,50) f[i] = dp[i] = -1;
    dp[0] = 1;
    dp[1] = 1;
    FOR(i,2,21) {
        dp[i] = 0;
        FOR(j,1,i) dp[i] += F(j) * dp[i-j];
    }
    cin >> t;
    while (t--) {
        cin >> n >> k;
        if (n <= 21 && k > DP(n)) {
            cout << -1 << "\n";
            continue;
        }
        solve(n, k, 1);
        cout << "\n";
    }
    return 0;
}
