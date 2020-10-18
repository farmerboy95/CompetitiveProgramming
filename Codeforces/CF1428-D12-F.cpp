/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - From https://codeforces.com/blog/entry/83771
        - More comments below
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
const int MAXN = 500010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], L[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        char ch;
        cin >> ch;
        a[i] = ch - '0';
    }
    ll now = 0, res = 0;
    FOR(i,1,n)
        // the histogram does not change when we meet 0
        if (a[i] == 0) res += now;
        else {
            // we handle the whole segment [l, r] of 1
            int l = i, r = i;
            while (r < n && a[r+1]) r++;
            // let L[x] be the largest l such that f(l, r) = x
            // we update L from 1 to r-l+1
            // we iterate and update res like when we move the right bound to the right one by one.
            FOR(j,1,r-l+1) {
                // when handling a specific j, L[k] (k < j) will be added by one
                // and L[j] will be l, so the sum of added value will be l + (j - 1) - L[j]
                now += l-1+j - L[j];
                res += now;
                // update L[j] to be the new value after handling the whole segment
                L[j] = r-j+1;
            }
            // update i to move to the next element after the segment of 1
            i = r;
        }
    cout << res;
    return 0;
}
