/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/hackercup/problem/112921602098268/
    Status: AC
    Idea:
        - Find the number of A, B (A > B) that N = A^2 + B^2
        - Max A should be about sqrt(max(N)), so we iterate through all A, try to find B and increase the result
        if B is found.
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n;
        int res = 0;
        FOR(i,0,46340) {
            int h = n - i * i;
            if (h < 0) break;
            int g = int(sqrt(h));
            if (g * g == h) {
                if (i >= g) {
                    res++;
                }
            }
        }
        cout << res << "\n";
    }
    return 0;
}
