/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use a + b = a XOR b + a AND b
        - So b[i] + c[i] = n * a[i] + sum(a[i]) (1)
        - Additionally, sum(b[i]) + sum(c[i]) = 2 * n * sum(a[i])
        => sum(a[i]) = (sum(b[i]) + sum(c[i])) / (2*n)
        - Replace sum(a[i]) to 1 we can find a[i], and this is the only array a
        - But the above equations are for sum of b and c, we need to recheck if the array a
        satisfies the statement condition.
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
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
ll b[MAXN], c[MAXN], B[MAXN], C[MAXN];
ll a[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> b[i];
    FOR(i,1,n) cin >> c[i];

    FOR(i,1,n)
        if (b[i] > c[i]) {
            cout << -1;
            return 0;
        }
    
    ll s = 0;
    FOR(i,1,n) s += b[i] + c[i];
    if (s % (2*n)) {
        cout << -1;
        return 0;
    }
    ll sum = s / 2 / n;

    FOR(i,1,n) {
        ll g = b[i] + c[i] - sum;
        if (g % n || g < 0) {
            cout << -1;
            return 0;
        }
        a[i] = g / n;
    }

    FOR(bit,0,29) {
        int cnt = 0;
        FOR(i,1,n)
            if (a[i] & (1<<bit)) cnt++;

        FOR(i,1,n)
            if (a[i] & (1<<bit)) B[i] += (ll) cnt * (1<<bit);
        
        FOR(i,1,n)
            if (a[i] & (1<<bit)) {
                C[i] += (ll) n * (1<<bit);
            } else {
                C[i] += (ll) cnt * (1<<bit);
            }
    }

    FOR(i,1,n)
        if (B[i] != b[i] || C[i] != c[i]) {
            cout << -1;
            return 0;
        }

    FOR(i,1,n) cout << a[i] << ' ';
    return 0;
}
