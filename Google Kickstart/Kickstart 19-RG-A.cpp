/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - If page i has been torn out, dd[i] = 0, otherwise, dd[i] = 1
        - For each reader (r), simply generate result for that reader, sum of dd[x] (x = k * r)
        - Time complexity O(t * n * ln(n))
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
const int MAXN = 300010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m, q, dd[100010], res[100010];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n >> m >> q;
        FOR(i,1,n) dd[i] = 1;
        FOR(i,1,m) {
            int x;
            cin >> x;
            dd[x] = 0;
        }
        // O(n * ln(n))
        // n/1 + n/2 + n/3 + ... + 1 = n * ln(n)
        FOR(len,1,n) {
            res[len] = 0;
            for (int j = len; j <= n; j += len) res[len] += dd[j];
        }
        ll rs = 0;
        while (q--) {
            int r;
            cin >> r;
            rs += res[r];
        }
        cout << rs << "\n";
    }
    return 0;
}
