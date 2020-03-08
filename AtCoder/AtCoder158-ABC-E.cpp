/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let x = a * 10 ^ y + b (y is length of b)
        - Suppose x % p = k => (a*10^y + b) % p = k
        - Now we want a % p = 0 (1) => b % p = k (2)
        - But from (2) to (1), we need 10^y % p != 0 => p not in {2, 5}
        - So we separately solve the problem with p = 2 or 5 (trivial) and the remaining cases
        using above observation.
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

int n, p;
string s;
int f[10000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> p >> s;
    s = " " + s;
    ll res = 0;
    if (p == 2) {
        FOR(i,1,n)
            if ((s[i] - '0') % 2 == 0) res += i;
    }
    else if (p == 5) {
        FOR(i,1,n)
            if ((s[i] - '0') % 5 == 0) res += i;
    }
    else {
        int now = 0;
        f[0] = 1;
        
        int mu = 1;
        FORE(i,n,1) {
            now = (now + mu * (s[i] - '0') % p) % p;
            res += f[now];
            f[now]++;
            mu = mu * 10 % p;
        }
    }
    cout << res;
    return 0;
}
