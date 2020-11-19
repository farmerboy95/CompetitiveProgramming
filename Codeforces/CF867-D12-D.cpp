/*
    Author: Nguyen Tan Bao
    Status: AC 
    Idea: 
        - https://codeforces.com/blog/entry/54888
        - https://codeforces.com/blog/entry/54888?#comment-388600
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
const int MAXN = 55;
const int MAXM = 5010;
const int MAXK = 16;
const int MAXQ = 200010;

int f[MAXN], s[MAXN], n, r;
ld p[MAXN], dp[MAXN][MAXM];

bool check(ld res) {
    MS(dp, 0);
    FORE(i,n,1)
        FOR(j,0,r) {
            if (j + f[i] <= r) {
                ld play = (f[i] + dp[i+1][j+f[i]]) * p[i];
                if (j + s[i] <= r) play += (s[i] + dp[i+1][j+s[i]]) * (1-p[i]);
                else play += (s[i] + res) * (1-p[i]);
                dp[i][j] = min(play, res);
            } else dp[i][j] = res;
        }
    return dp[1][0] < res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> r;
    FOR(i,1,n) {
        cin >> f[i] >> s[i] >> p[i];
        p[i] /= 100;
    }
    ld dau = 0, cuoi = 1e10;
    FOR(o,1,100) {
        ld mid = (dau + cuoi) / 2;
        if (check(mid)) cuoi = mid;
        else dau = mid;
    }
    cout << fixed << setprecision(9) << dau;
    return 0;
}
