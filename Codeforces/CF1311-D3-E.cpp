/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/74224
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
const int MAXN = 5010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int t, n, d, par[MAXN], depth[MAXN], deg[MAXN];
bool bad[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n >> d;
        int upper = n * (n-1) / 2;
        int lower = 0, cntDepth = 0;
        FOR(i,2,n) {
            if (!(i & (i-1))) cntDepth++;
            lower += cntDepth;
        }
        if (!(lower <= d && d <= upper)) {
            cout << "NO\n";
            continue;
        }

        // init
        FOR(i,1,n) {
            par[i] = i-1;
            depth[i] = i-1;
            bad[i] = false;
            deg[i] = 1;
        }
        deg[n] = 0;

        int now = n * (n-1) / 2;
        while (now > d) {
            int v = -1;
            // choose a leaf v with smallest depth
            FOR(i,1,n)
                if (!bad[i] && deg[i] == 0 && (v == -1 || depth[v] > depth[i])) v = i;
            // find such vertex p that its depth is less than the depth of v by 2 and it has less than 2 children
            int p = -1;
            FOR(i,1,n)
                if (deg[i] < 2 && depth[i] < depth[v] - 1 && (p == -1 || depth[i] > depth[p])) p = i;
            if (p == -1) {
                bad[v] = true;
                continue;
            }
            // move v to be a child of p
            deg[par[v]]--;
            depth[v]--;
            deg[p]++;
            par[v] = p;
            now--;
        }

        cout << "YES\n";
        FOR(i,2,n) cout << par[i] << ' ';
        cout << "\n";
    }
    return 0;
}
