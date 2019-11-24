/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let dp[i] is the minimum number of steps needed to go from i to n
        - dp[n] = 0
        - dp[i] = min(dp[j]) + 1 (j is from i+1 to i+m)
        - Use sliding window technique to find dp[i]
        - Trace result by going from 0, take the first j that has dp[j] = dp[i] - 1, 
        it will be the smallest lexicographically sequence
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
const int MAXN = 100010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, dp[MAXN];
string s;
deque<II> window;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    cin >> s;
    dp[n] = 0;
    window.push_back(II(dp[n], n));
    FORE(i,n-1,0) {
        while (window.front().SE > i + m) window.pop_front();
        if (s[i] == '1') dp[i] = 1000000000;
        else {
            if (window.front().FI == 1000000000) {
                cout << -1;
                return 0;
            } 
            dp[i] = window.front().FI + 1;
        }

        while (!window.empty() && window.back().FI >= dp[i]) window.pop_back();
        window.push_back(II(dp[i], i));
    }

    int now = 0;
    while (now < n) {
        int nex = -1;
        FOR(i,now+1,n) {
            if (dp[i] == dp[now] - 1) {
                nex = i;
                break;
            }
        }
        cout << nex - now << ' ';
        now = nex;
    }
    return 0;
}
