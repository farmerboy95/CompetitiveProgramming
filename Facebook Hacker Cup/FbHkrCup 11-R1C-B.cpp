/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/hackercup/problem/157714037613443/
    Status: AC
    Idea:
        - Simulate how to divide polynomials.
        - Divide from the largest term to the smallest possible term.
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

int n, m, a[MAXN], b[MAXN], c[MAXN], d[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n;
        FOR(i,0,n) cin >> a[i];
        cin >> m;
        FOR(i,0,m) cin >> b[i];
        if (n < m) {
            cout << "no solution\n";
            continue;
        }
        bool co = true;
        FORE(i,n,m) {
            int u = a[i], v = b[m];
            if (u % v) {
                co = false;
                break;
            }
            c[i-m] = u / v;
            MS(d, 0);
            int itr = i;
            FORE(j,m,0) d[itr--] = c[i-m] * b[j];
            FORE(j,i,0) a[j] -= d[j];
        }
        if (co)
            FOR(i,0,n)
                if (a[i]) co = false;
        if (!co) cout << "no solution\n";
        else {
            FOR(i,0,n-m) cout << c[i] << ' ';
            cout << "\n";
        }
    }
    return 0;
}
