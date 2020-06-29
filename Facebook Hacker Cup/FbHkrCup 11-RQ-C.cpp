/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/hackercup/problem/188558297823727/
    Status: AC
    Idea:
        - Let dp[mask] = the lexicographically smallest string formed by the words in the mask
        - Result is dp[(1<<n)-1]
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
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
string s[MAXN];
string dp[1000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n;
        FOR(i,1,n) cin >> s[i];
        
        dp[0] = "";
        FOR(mask,1,(1<<n)-1) {
            dp[mask] = "";
            FOR(i,1,n)
                if (mask & (1<<(i-1))) {
                    string w = dp[mask ^ (1<<(i-1))] + s[i];
                    if (dp[mask] == "") dp[mask] = w;
                    else if (dp[mask] > w) dp[mask] = w;
                }
        }

        cout << dp[(1<<n)-1] << "\n";
    }
    return 0;
}
