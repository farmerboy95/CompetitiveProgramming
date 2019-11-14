/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Because all numbers are distinct, we put them all into an array f, with f[i] is the person who gets the problem i
        - Let dp1[i] is minimum number of swaps needed to let person 1 getting problems from 1 to i
        - Let dp2[i] is minimum number of swaps needed to let person 1 and 2 getting problems from 1 to i
        - Let dp3[i] is minimum number of swaps needed to let person 1, 2 and 3 getting problems from 1 to i
        - Result is min(dp1[n], dp2[n], dp3[n]) (n = k1 + k2 + k3)
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
const int MAXM = 600010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m, p, f[MAXN], dp1[MAXN], dp2[MAXN], dp3[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> p;
    FOR(i,1,n) { int x; cin >> x; f[x] = 1; }
    FOR(i,1,m) { int x; cin >> x; f[x] = 2; }
    FOR(i,1,p) { int x; cin >> x; f[x] = 3; }
    n = n+m+p;

    FOR(i,1,n) dp1[i] = dp1[i-1] + (f[i] != 1);

    FOR(i,1,n) dp2[i] = min(dp2[i-1], dp1[i-1]) + (f[i] != 2);

    FOR(i,1,n) dp3[i] = min(dp3[i-1], min(dp2[i-1], dp1[i-1])) + (f[i] != 3);

    cout << min(dp1[n], min(dp2[n], dp3[n]));

    return 0;
}
