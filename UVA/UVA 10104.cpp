/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Use Extended Euclid Algorithm
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

int extendedEuclid(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int X1, Y1;
    int d = extendedEuclid(b, a % b, X1, Y1);
    x = Y1;
    y = X1 - Y1 * (a / b);
    return d;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int a, b;
    while (cin >> a >> b) {
        int x, y;
        int d = extendedEuclid(a, b, x, y);
        cout << x << ' ' << y << ' ' << d << "\n";
    }
    return 0;
}
