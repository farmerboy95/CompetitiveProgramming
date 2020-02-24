/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Consider one tuple (n, x, m), we need to print number of j (0 <= j < n-1) that 
        (a[j] % m) < (a[j+1] % m)
        - Each pair (j, j+1) we have 3 possibilities: larger, equal and smaller. Our result
        will be n - 1 - (number of larger pairs) - (number of equal pairs)
        - For equal pairs, we can calculate the number of d[i] % m == 0 within n-1 times d[i]
        is used in our sequence.
        - For larger pairs, we have a[i] = x + d[0 % k] + d[1 % k] + ... + d[(i-1) % k], 
        and a[i] % m > a[i+1] % m <=> a[i] % m > (a[i] % m + d[i % k] % m) % m, this means our
        d[i % k] makes the sum exceeded m, so we can simply get SUM = (x % m + sum(d[i%k] % m))
        (0 <= i <= n-2), then the number of larger pairs = SUM / m
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
const int MAXK = 5010;
const int MAXQ = 200010;

int k, q, n;
ll d[MAXK], m, x, D[MAXK];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> k >> q;
    FOR(i,0,k-1) cin >> d[i];
    while (q--) {
        cin >> n >> x >> m;
        FOR(i,0,k-1) D[i] = d[i] % m;

        ll cnt0 = 0;
        FOR(i,0,k-1) cnt0 += (D[i] == 0);

        ll caseEqual = cnt0 * ((n-1) / k);
        FOR(i,0,(n-1)%k - 1) caseEqual += (D[i] == 0);

        ll caseBigger = x % m;
        ll sumD = 0;
        FOR(i,0,k-1) sumD += D[i];
        caseBigger += (n-1)/k * sumD;
        FOR(i,0,(n-1)%k - 1) caseBigger += D[i];
        caseBigger /= m;

        cout << n-1 - caseEqual - caseBigger << "\n";
    }
    return 0;
}
