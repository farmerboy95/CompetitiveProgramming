/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Sort all a[i] increasingly
        - If all students are in 1 team, the diversity is a[n] - a[1]
        - If we have 2 teams, the diversity is a[n] - a[1] - (a[i+1] - a[i]) (one team contains students
        from 1 to i, the other contains students from i+1 to n)
        - How to make the diversity smallest? (a[i+1] - a[i]) must be biggest, or we can choose element b[i+1] = a[i+1] - a[i].
        - So let dp[i] is the biggest sum of chosen elements in array b, so that n students can be divided into teams
        that satisfies the problem requirement.
            + dp[i] = max(dp[i-1], dp[i-3] + b[i]) (i: 4 -> n-2)
        - Add array "trace" to get the specific result.
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
const int MAXN = 200010;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;

struct Data {
    int val, cs;
    Data(int val = 0, int cs = 0) : val(val), cs(cs) {}
};

bool operator< (Data a, Data b) {
    return a.val < b.val;
}

int n, b[MAXN], dp[MAXN], trace[MAXN], res[MAXN];
Data a[MAXN];
bool f[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i].val;
        a[i].cs = i;
    }
    sort(a+1, a+n+1);

    FOR(i,2,n) b[i] = a[i].val - a[i-1].val;

    FOR(i,4,n-2) {
        if (dp[i-3] + b[i] > dp[i-1]) {
            dp[i] = dp[i-3] + b[i];
            trace[i] = i-3;
        }
        else {
            dp[i] = dp[i-1];
            trace[i] = i-1;
        }
    }

    int u = n-2;
    while (u >= 4) {
        if (u - trace[u] > 1) f[u] = true;
        u = trace[u];
    }
    int cnt = 1;
    FOR(i,1,n) {
        if (f[i]) cnt++;
        res[a[i].cs] = cnt;
    }
    cout << a[n].val - a[1].val - dp[n-2] << ' ' << cnt << "\n";
    FOR(i,1,n) cout << res[i] << ' ';
    return 0;
}