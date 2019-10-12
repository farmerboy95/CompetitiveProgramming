/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/Baltic/official/boi2008_solutions/gloves-sol-en.pdf

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
const int MAXN = 21;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, a[MAXN], b[MAXN];
vector<II> c, d;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) cin >> b[i];
    // get all pairs rectangles
    FOR(mask,0,(1<<n)-1) {
        int l = 0, r = 0;
        FOR(i,1,n)
            if (mask & (1<<(i-1))) l += a[i];
            else r += b[i];
        c.push_back(II(l, r));
    }
    sort(ALL(c));
    // get staircase polygon
    FOR(i,0,SZ(c)-1) {
        while (SZ(d) && d.back().SE <= c[i].SE) d.pop_back();
        d.push_back(c[i]);
    }
    // get result
    ll resX = 2000000000, resY = 2000000000;
    FOR(i,1,SZ(d)-1)
        if ((ll) d[i-1].FI+1 + d[i].SE+1 < resX + resY) {
            resX = d[i-1].FI + 1;
            resY = d[i].SE + 1;
        }
    cout << resX << "\n" << resY;
    return 0;
}
