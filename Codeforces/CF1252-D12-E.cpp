/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://github.com/jonathanirvings/icpc-jakarta-2019/blob/master/problem_analysis.pdf
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
typedef pair<ll, int> IIl;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, l, r, k, low[MAXN], high[MAXN], a[MAXN], res[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> l >> r >> k;
    FOR(i,1,n) cin >> a[i];
    low[n] = l;
    high[n] = r;
    FORE(i,n-1,1) {
        if (a[i] < a[i+1]) {
            low[i] = max(l, low[i+1] - k);
            high[i] = high[i+1] - 1;
        }
        else if (a[i] > a[i+1]) {
            low[i] = low[i+1] + 1;
            high[i] = min(r, high[i+1] + k);
        }
        else {
            low[i] = low[i+1];
            high[i] = high[i+1];
        }
    }

    FOR(i,1,n)
        if (low[i] > high[i] || low[i] > r || high[i] < l) {
            cout << -1;
            return 0;
        }

    res[1] = low[1];
    FOR(i,2,n) {
        if (a[i] == a[i-1]) {
            res[i] = res[i-1];
        }
        else if (a[i] < a[i-1]) {
            res[i] = max(low[i], res[i-1] - k);
        }
        else {
            res[i] = max(low[i], res[i-1] + 1);
        }
    }
    FOR(i,1,n) cout << res[i] << ' ';
    return 0;
}
