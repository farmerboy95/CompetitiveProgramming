/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: https://codeforces.com/blog/entry/70654
    Sample Code: https://codeforces.com/contest/1236/submission/62807169
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
const int MAXN = 200010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

II merge(II A, II B) {
    if (A == II(-1, -1)) return B;
    if (B == II(-1, -1)) return A;
    return II(min(A.FI, B.FI), max(A.SE, B.SE));
}

int n, m, a[MAXN];
II val[MAXN], res[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) cin >> a[i];
    // corner case, cannot avoid being guessed
    if (n == 1) {
        cout << 0;
        return 0;
    }

    // init result range
    FOR(i,1,n) res[i] = II(-1, -1);

    // --------------------------------------------------------------------------------------------
    // find right bound
    int l = 200000 - n + 1; 
    int r = l - 1 + n;
    FOR(i,1,r) val[i] = II(-1, -1);
    FOR(i,l,r) val[i] = II(i-l+1, i-l+1);

    FOR(i,1,m) {
        // move all elements in pos to the left, merge with available one on the left of it
        int pos = a[i] - i + l - 1;
        val[pos-1] = merge(val[pos], val[pos-1]);
        val[pos] = II(-1, -1);
    }

    // get right bound of each element, as we can move m+1 times
    FOR(i,1,200000)
        if (val[i] != II(-1, -1)) 
            FOR(j,val[i].FI,val[i].SE) res[j].SE = min(i + m + 1, r) - l + 1;

    // --------------------------------------------------------------------------------------------
    // find left bound
    l = 1; r = n;
    FOR(i,1,200000) val[i] = II(-1, -1);
    FOR(i,1,n) val[i] = II(i,i);

    FOR(i,1,m) {
        // move all elements in pos to the right, merge with available one on the right of it
        int pos = a[i] + i;
        val[pos+1] = merge(val[pos], val[pos+1]);
        val[pos] = II(-1, -1);
    }

    // get left bound of each element, as we can move m+1 times
    FOR(i,1,200000)
        if (val[i] != II(-1, -1))
            FOR(j,val[i].FI,val[i].SE) res[j].FI = max(i - m - 1, 1);

    // simply get the result
    ll kq = 0;
    FOR(i,1,n) kq += res[i].SE - res[i].FI + 1;
    cout << kq;
    return 0;
}
