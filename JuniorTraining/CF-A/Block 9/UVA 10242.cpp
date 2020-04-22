/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Get the common point, then use vector to find the fourth point.
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
} a[4], b[4];

bool isEqual(Point a, Point b) {
    return abs(a.x - b.x) < EPS && abs(a.y - b.y) < EPS;
}

void printResult() {
    FOR(i,0,3)
        FOR(j,i+1,3)
            if (isEqual(a[i], a[j])) {
                FOR(k,0,3)
                    if (k != i && k != j)
                        FOR(l,0,3)
                            if (l != k && l != i && l != j) {
                                Point p = Point(a[k].x - a[i].x, a[k].y - a[i].y);
                                Point q = Point(a[l].x + p.x, a[l].y + p.y);
                                cout << fixed << setprecision(3) << q.x << ' ' << q.y << "\n";
                                return;
                            }
            }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    while (cin >> a[0].x >> a[0].y) {
        FOR(i,1,3) cin >> a[i].x >> a[i].y;
        printResult();
        
    }
    return 0;
}
