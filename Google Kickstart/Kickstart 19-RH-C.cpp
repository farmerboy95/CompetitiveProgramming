/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[i][j][k] is whether we can create a number from digits from 1 to i, the difference between
        positive numbers and negative number is j, sum of them modulo 11 is k
        - Try to maintain j of each i to not exceed 100 => j <= 900 * 2 = 1800
        - Reason: https://codeforces.com/blog/entry/71373?#comment-558602
        - Using this reason to limit the difference between positive part and negative part of each j
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
const int MAXN = 210;
const int MAXM = 100010;
const int MAXK = 110;
const int MAXQ = 200010;

int a[MAXN];
bool dp[10][2000][15];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        FOR(i,1,9) cin >> a[i];
        int n = 0;
        FOR(i,1,9) n += a[i];
        MS(dp, 0);
        dp[0][900][0] = true;
        FOR(i,1,9)
            FOR(j,0,1800)
                FOR(k,0,10)
                    if (dp[i-1][j][k]) {
                        int st = a[i] % 2;
                        for (int diff = st; diff <= 100; diff += 2) {
                            if ((a[i] + diff) / 2 > a[i]) continue;
                            if ((a[i] - diff) / 2 < 0) continue;
                            int m = ((diff % 11 + 11) % 11) * i % 11;
                            if (j + diff >= 0 && j + diff <= 1800) dp[i][j+diff][(k + m) % 11] = true;
                        }
                        for (int diff = -st; diff >= -100; diff -= 2) {
                            if ((a[i] - diff) / 2 > a[i]) continue;
                            if ((a[i] + diff) / 2 < 0) continue;
                            int m = ((diff % 11 + 11) % 11) * i % 11;
                            if (j + diff >= 0 && j + diff <= 1800) dp[i][j+diff][(k + m) % 11] = true;
                        }
                    }
        if (dp[9][900 + n % 2][0]) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
