/*
    Author: Nguyen Tan Bao
    Status: Can't solve so far - AC after reading editorial
    Approach:
        - I tried to solve this problem backward. 
        Find number of groups of A[i] to make AND sum = 0 => Result = number of groups - number of groups that have AND sum != 0
        - Let f(x) = number of A[i] where A[i] & x = x
        => Number of groups that have AND sum is x = 2 ^ f(x)
        - Use inclusion-exclusion to find the result (+ 2 ^ f(x) if number of 1-bit in x is even and - 2 * f(x) if number of 1-bit in x is odd)
        - Could not find f(x) so far => read editorial
    Idea: https://codeforces.com/blog/entry/13112
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
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

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 2000010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, a[MAXN], f[MAXN], dp[25][MAXN];

ll binPowMod(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];

    // calculate dp
    FOR(i,1,n) dp[0][a[i]]++;
    FOR(i,0,19) {
        FOR(j,0,1000000) {
            if (j & (1 << i)) {
                dp[i+1][j] = dp[i][j];
            }
            else {
                dp[i+1][j] = dp[i][j] + dp[i][j + (1<<i)];
            }
        }
    }

    // find res using inclusion-exclusion
    ll res = (binPowMod(2, n, MODBASE) - 1 + MODBASE) % MODBASE;
    FOR(i,1,1000000) {
        int numBit = __builtin_popcount(i);
        ll cnt = (binPowMod(2, dp[20][i], MODBASE) - 1 + MODBASE) % MODBASE;
        if (numBit % 2) {
            res = (res - cnt + MODBASE) % MODBASE;
        }
        else {
            res = (res + cnt) % MODBASE;
        }
    }
    cout << res;
    return 0;
}
