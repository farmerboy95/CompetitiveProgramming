/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - If x and y are coprime, it's a good choice
        - Prove using Euclid theorem ax + by = c
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 260;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

int x, y;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    while (cin >> x >> y) {
        int g = gcd(x, y);
        string res = "";
        if (g > 1) res = "Bad Choice";
        else res = "Good Choice";
        printf("%10d%10d    %s\n\n", x, y, res.c_str());
    }
    return 0;
}
