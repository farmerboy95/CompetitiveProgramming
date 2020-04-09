/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Adding a number will keep or increase the result
        - After writing out list of divisors of each number from 2 to n in increasing order, we can
        easily see that it's optimal to add the largest divisor before adding the number itself to the
        set, and by adding the number itself, the result maybe min(currentResult, largestDivisor).
        - So we call f[i] = largest divisor of number i, f[1] = 1. Sort all f[i] and print array f.
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

int n, nt[MAXN], f[MAXN];

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            nt[i] = i;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    sieveBase(500000);
    cin >> n;
    f[1] = 1;
    FOR(i,2,n) {
        f[i] = i;
        int g = i, Min = 1000000000;
        while (g > 1) {
            Min = min(Min, nt[g]);
            g = g / nt[g];
        }
        f[i] /= Min;
    }
    sort(f+1, f+n+1);
    FOR(i,2,n) cout << f[i] << ' ';
    return 0;
}
