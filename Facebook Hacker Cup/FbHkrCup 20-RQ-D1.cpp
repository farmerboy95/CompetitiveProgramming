/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2020/qualification-round/problems/D1
    Status: AC
    Idea:
        - Let dp[i] is the minimum cost to go to city i. Initially, dp[1] = 0.
        => dp[i] = dp[j] + c[j] (i - j <= M).
        - This would take us O(N^2) to calculate. To reduce the complexity, we store pair(dp[i] + c[i], i)
        to a min heap (priority queue). When we take a pair out of the heap, we should check if the position
        satisfies the above condition or not. If not, we remove it from the heap because we are not going to
        use it in later steps. One pair will be put into / taken out of the heap at most once.
        - Note that if we can't pick any pair from heap, dp[i] = -1, and we don't put it into heap.
        - Complexity O(NlogN)
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
typedef pair<ll, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int a[MAXN], t, n, m;
ll dp[MAXN];
priority_queue<II, vector<II>, greater<II> > h;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";

        cin >> n >> m;
        FOR(i,1,n) cin >> a[i];

        MS(dp, 0);

        while (!h.empty()) h.pop();
        dp[1] = 0;
        h.push(II(dp[1], 1));

        FOR(i,2,n) {
            ll picked = -1;
            while (SZ(h)) {
                II r = h.top();
                if (r.SE < i - m) {
                    h.pop();
                    continue;
                }
                picked = r.FI;
                break;
            }
            if (picked == -1) {
                dp[i] = -1;
                continue;
            }
            dp[i] = picked;
            if (a[i]) h.push(II(dp[i] + a[i], i));
        }
        cout << dp[n] << "\n";
    }
    return 0;
}
