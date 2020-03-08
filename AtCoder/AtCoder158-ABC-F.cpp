/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Sort the initial array based on X[i]
        - Let dp[i] is the number of sets of robots remaining after operations on robots [1..i]
        - So for each i, we consider robot (i+1)th, we have 2 choices, activating it or not activating it.
        - If we leave it there, dp[i+1] += dp[i], obviously
        - If we activate robot (i+1)th, we have to find robot (x)th, which is the furthest robot activated
        as the result of activation of robot (i+1)th. So dp[x] += dp[i]
        - So how to find x? Imagine robot journey as a segment, so we have to merge overlap segments from segment
        i+1 until we cannot merge anymore. But it would take O(n). At next steps we may have to remove previous
        segment to find the big segment once again. 
        - Why don't we do it reversely? Merge segments from n to i, and store f[i] = right endpoint of merged segment, 
        use a set to store segments and keep pulling them out while we can merge them with segment i.
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, f[MAXN];
int dp[MAXN];
II a[MAXN];
set<II> s;
int MOD = 998244353;

void preProcess() {
    sort(a+1, a+n+1);
    FORE(i,n,1) {
        II r = a[i];
        while (1) {
            set<II>::iterator it = s.lower_bound(r);
            if (it == s.end()) break;
            if (r.SE < it->FI) break;
            r.SE = max(r.SE, it->SE);
            s.erase(it);
        }
        f[i] = r.SE;
        s.insert(r);
    }
}

int activate(int u) {
    int r = f[u];
    int dau = 1, cuoi = n;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (a[mid].FI > r) cuoi = mid-1;
        else dau = mid+1;
    }
    return cuoi;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        int u, v;
        cin >> u >> v;
        a[i] = II(u, u+v-1);
    }
    preProcess();
    dp[0] = 1;
    FOR(i,0,n-1) {
        dp[i+1] = (dp[i+1] + dp[i]) % MOD;
        int x = activate(i+1);
        dp[x] = (dp[x] + dp[i]) % MOD;
    }
    cout << dp[n];
    return 0;
}
