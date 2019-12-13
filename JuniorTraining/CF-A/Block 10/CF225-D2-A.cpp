/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
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
const int MAXN = 210;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, x, a[10];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    cin >> x;
    int y = 7 - x;
    FOR(i,1,n) {
        cin >> a[0] >> a[1];
        a[2] = 7 - a[0];
        a[3] = 7 - a[1];
        FOR(i,0,3)
            if (a[i] == x || a[i] == y) {
                cout << "NO";
                return 0;
            }
    }
    cout << "YES";
    return 0;
}
