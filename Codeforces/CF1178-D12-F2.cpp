/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://codeforces.com/blog/entry/68534
        - More comments in code
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
const int MAXN = 510;
const int MAXM = 1000010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;
ll dp[2*MAXN][2*MAXN];
vector<int> a, c, pos[MAXN];
ll MOD = 998244353;

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    // input
    FOR(i,1,m) {
        int x;
        cin >> x;
        c.push_back(x);
    }

    // compress the input
    a.push_back(-1);
    FOR(i,0,m-1)
        if (a.back() != c[i]) a.push_back(c[i]);
    // m = number of elements in the compressed array
    m = SZ(a)-1;
    // corner case
    if (m > 2*n) {
        cout << 0;
        return 0;
    }

    // pos[i] contains positions of number i in the compressed array
    FOR(i,1,m) pos[a[i]].push_back(i);
    // init dp
    // dp[l][r] = number of ways to color segment [l, r]
    FOR(i,0,m+1)
        FOR(j,0,m+1) dp[i][j] = 1;

    FOR(len,1,m)
        for (int lef = 1; lef + len - 1 <= m; lef++) {
            // for each [left, right] with increasing length
            int rig = lef + len - 1;
            // p = smallest number in the segment
            int p = a[lef];
            FOR(i,lef+1,rig) p = min(p, a[i]);
            // if there are some elements outside the segment equal to p => dp[left][right] = 0
            int Min = pos[p][0], Max = pos[p].back();
            if (Min < lef || Max > rig) {
                dp[lef][rig] = 0;
                continue;
            }

            // now we need to choose segment [g+1, h] to paint color p, as each side are independant
            // to each other, we calculate each side seperately.
            ll sumLef = 0, sumRig = 0;
            FOR(g,lef-1,Min-1) sumLef = add(sumLef, mul(dp[lef][g], dp[g+1][Min-1]));
            FOR(h,Max,rig) sumRig = add(sumRig, mul(dp[Max+1][h], dp[h+1][rig]));
            dp[lef][rig] = mul(sumLef, sumRig);
            
            // now let's continue to paint in the middle of 2 consecutive p ones
            FOR(i,0,SZ(pos[p])-2)
                if (pos[p][i] + 1 != pos[p][i+1]) dp[lef][rig] = mul(dp[lef][rig], dp[pos[p][i]+1][pos[p][i+1]-1]);
        }
    cout << dp[1][m];

    return 0;
}
