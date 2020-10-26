/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/84056
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

ll solve(ll a, ll b, ll c, ll d) {
    // a > b*c => -1 as indicated in the editorial
    if (a > b * c) return -1;

    // a <= b*c, this is a bit different from editorial, we can use the pictures in it
    // we consider t <= c, not t < c
    ll p = c / d, q = c % d;
    // let's check out the last -a when t <= c, there will be q last moments with full of b
    // so let's check out the q+1 last moments when t <= c (1 moment when we deal the damage
    // and q moment with full of b), it would be pdb + qb, if this sum < a => -1
    if (a - p * d * b - q * b > 0) return -1;
    // now we can forget last q moments
    // need to find greatest k that a > bdk, should not exceed p
    ll k = a / b / d;
    if (b * d * k >= a) k--;
    k = min(k, p);
    // we can get the result with the help of the pictures
    return a * (k + 1) - d * b * k * (k + 1) / 2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << solve(a, b, c, d) << "\n";
    }
    return 0;
}
