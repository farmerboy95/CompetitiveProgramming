/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/84758?#comment-723626
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
const int MAXN = 2010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, k, f[MAXN][MAXN], pref[MAXN], suff[MAXN];
II a[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    FOR(i,1,m) cin >> a[i].FI >> a[i].SE;
    
    sort(a+1, a+m+1, [](II x, II y) {
        return x.FI + x.SE < y.FI + y.SE;
    });

    FOR(l,1,n-k+1) {
        FOR(i,1,m) {
            int L = max(a[i].FI, l);
            int R = min(a[i].SE, l + k - 1);
            f[i][l] = max(0, R - L + 1);
        }
    }

    FOR(l,1,n-k+1) {
        int sum = 0;
        FOR(i,1,m) {
            sum += f[i][l];
            pref[i] = max(pref[i], sum);
        }

        sum = 0;
        FORE(i,m,1) {
            sum += f[i][l];
            suff[i] = max(suff[i], sum);
        }
    }

    int res = 0;
    FOR(i,0,m) res = max(res, pref[i] + suff[i+1]);
    cout << res;
    return 0;
}
