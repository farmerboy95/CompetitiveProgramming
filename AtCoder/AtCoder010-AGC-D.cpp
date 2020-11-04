/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://img.atcoder.jp/agc010/editorial.pdf
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN];

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

bool solve() {
    // one of the numbers is 1 => get sum of (a[i]-1)
    bool co = false;
    FOR(i,1,n)
        if (a[i] == 1) co = true;
    if (co) {
        ll sum = 0;
        FOR(i,1,n) sum += a[i] - 1;
        if (sum % 2) return true;
        return false;
    }

    // odd number of even integers => win
    int even = 0;
    FOR(i,1,n) even += (a[i] % 2 == 0);
    if (even % 2) return true;

    // even number of even integers and two or more odd ones => lose
    int odd = n - even;
    if (odd >= 2) return false;

    // otherwise, simulate the game
    FOR(i,1,n)
        if (a[i] % 2) {
            a[i]--;
            break;
        }
    int g = a[1];
    FOR(i,1,n) g = gcd(g, a[i]);
    FOR(i,1,n) a[i] /= g;
    return 1 - solve();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    if (solve()) cout << "First";
    else cout << "Second";
    return 0;
}
