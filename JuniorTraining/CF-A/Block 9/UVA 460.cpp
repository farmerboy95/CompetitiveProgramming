/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Simply get max coordinates of lower left points and min coordinates of upper right points
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

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
} a[3], b[3];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        FOR(i,0,1) cin >> a[i].x >> a[i].y >> b[i].x >> b[i].y;
        a[2].x = max(a[0].x, a[1].x);
        a[2].y = max(a[0].y, a[1].y);
        b[2].x = min(b[0].x, b[1].x);
        b[2].y = min(b[0].y, b[1].y);
        if (a[2].x < b[2].x && a[2].y < b[2].y) {
            cout << a[2].x << ' ' << a[2].y << ' ' << b[2].x << ' ' << b[2].y;
        }
        else cout << "No Overlap";
        cout << "\n";
        if (t) cout << "\n";
    }
    return 0;
}
