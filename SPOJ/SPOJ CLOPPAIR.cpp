/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://www.topcoder.com/community/competitive-programming/tutorials/line-sweep-algorithms/
        - Closest pair part
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
const int MAXN = 50010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

struct Point {
    ll x, y;
    int cs;
    Point(ll x = 0, ll y = 0, int cs = 0) : x(x), y(y), cs(cs) {}
    bool operator< (const Point &p) const {
        if (y == p.y) return x < p.x;
        return y < p.y;
    }
};

bool cmp(Point a, Point b) {
    return a.x < b.x;
}

Point a[MAXN];
int n;
set<Point> box;

ld dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i].x >> a[i].y;
        a[i].cs = i-1;
    }
    sort(a+1, a+n+1, cmp);
    ld best = 1e18;
    box.insert(a[1]);
    int pA, pB;
    int lef = 1;
    FOR(i,2,n) {
        while (lef < i && a[i].x - a[lef].x > best) box.erase(a[lef++]);
        for (set<Point>::iterator it = box.lower_bound(Point(0, (ll) ceil(a[i].y - best))); it != box.end() && a[i].y + best >= it->y; it++) {
            ld dis = dist(*it, a[i]);
            if (dis < best) {
                best = dis;
                pA = a[i].cs;
                pB = it->cs;
            }
        }
        box.insert(a[i]);
    }
    if (pA > pB) swap(pA, pB);
    cout << pA << ' ' << pB << ' ' << fixed << setprecision(6) << best;
    return 0;
}
