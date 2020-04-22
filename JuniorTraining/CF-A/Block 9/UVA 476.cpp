/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Simply check if a point is inside a rectangle or not
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
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}
};

Point a[110], b[110];
int n;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    char ch;
    while (cin >> ch) {
        if (ch == '*') break;
        n++;
        cin >> a[n].x >> a[n].y >> b[n].x >> b[n].y;
    }
    ld x, y;
    int cnt = 0;
    while (cin >> x >> y) {
        bool co = false;
        cnt++;
        if (x == 9999.9 && y == 9999.9) break;
        // cout << x << ' ' << y << endl;
        FOR(i,1,n) {
            if (x < b[i].x && x > a[i].x && y < a[i].y && y > b[i].y) {
                co = true;
                cout << "Point " << cnt << " is contained in figure " << i << "\n";
            }
        }
        if (!co) cout << "Point " << cnt << " is not contained in any figure\n";
    }
    return 0;
}
