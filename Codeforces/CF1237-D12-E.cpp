/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/70620
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
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int k = 1;
    FOR(i,1,20) {
        cout << k << ' ' << k + 1 << endl;
        if (n == k || n == k+1) {
            cout << 1;
            return 0;
        }
        if (k % 2) k = (k + 1) * 2;
        else k = k * 2 + 1;
    }
    cout << 0;
    return 0;
}
