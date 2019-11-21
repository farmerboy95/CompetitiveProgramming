/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The satisfied and unsatisfied board form a new board just like a chessboard
        - Remember to handle the case when N = n - 7 is odd and M = m - 7 is odd
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m, c;
    while (cin >> n >> m >> c) {
        if (n + m + c == 0) break;

        int N = n - 8 + 1;
        int M = m - 8 + 1;
        int res = N * M / 2;
        if (N * M % 2) res += c;
        cout << res << "\n";
    }
    return 0;
}
