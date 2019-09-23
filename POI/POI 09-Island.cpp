/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea:
        - For each city a, we should use the passable road (a, b) which has b max
        - Just like dp convex hull technique, we add roads from 1 to n-1 which has decreasing slope
        - Useful figure: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2009/editorial/wsp.pdf
        - More or less like this submission: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2009/code/wsp/prog/wys.cpp
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<ll, ll> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 1000010;
const int MAXK = 110;
const int MAXQ = 200010;

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}
};

struct Vector {
    ld x, y;
    Vector(ld x = 0, ld y = 0) : x(x), y(y) {}
};

Vector toVec(Point a, Point b) {
    return Vector(b.x - a.x, b.y - a.y);
}

inline int cmp(ld a, ld b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

ld distance(Point a, Point b) {
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

struct Line {
    ld a, b, c;
    Point A, B;
    Line(ld a = 0, ld b = 0, ld c = 0) : a(a), b(b), c(c) {} 
    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    Line(Point P, ld m) {
        a = -m; b = 1;
        c = -((a * P.x) + (b * P.y));
    }
    ld f(Point A) {
        return a*A.x + b*A.y + c;
    }
};

ld crossProduct(Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

bool ccw(Point a, Point b, Point c) {
    // cout << a.x << ' ' << a.y << endl;
    // cout << b.x << ' ' << b.y << endl;
    // cout << c.x << ' ' << c.y << endl;
    // cout << crossProduct(toVec(a, b), toVec(a, c)) << endl;
    return cmp(crossProduct(toVec(a, b), toVec(a, c)), 0) > 0;
}

bool areParallel(Line l1, Line l2) {
    return cmp(l1.a*l2.b, l1.b*l2.a) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false; 
    ld dx = l1.b*l2.c - l2.b*l1.c;
    ld dy = l1.c*l2.a - l2.c*l1.a;
    ld d = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}

int n, m, road[MAXN];
Point a[MAXN];
II b[MAXM];
vector<II> convexList;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) {
        int u, v;
        cin >> u >> v;
        a[i] = Point(u, v);
    }
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        b[i] = II(u, v);
    }
    sort(b+1, b+m+1);

    // find furthest passable road (a, b) of each city a (a < b, b max)
    int roadIdx = m;
    FORE(i,n,1) {
        road[i] = -1;
        int now = n;
        while (roadIdx >= 1 && b[roadIdx].FI == i && b[roadIdx].SE == now) {
            now--;
            roadIdx--;
        }
        if (now > i) road[i] = now;
        while (roadIdx >= 1 && b[roadIdx].FI == i) roadIdx--;
    }

    // find result
    convexList.push_back(II(1, road[1]));
    FOR(i,2,n) {
        if (road[i] == -1) continue;

        int w = SZ(convexList)-1;
        if (ccw(a[convexList[w].FI], a[convexList[w].SE], a[road[i]])) continue;

        while (w >= 1) {
            Point r;
            areIntersect(Line(a[convexList[w].FI], a[convexList[w].SE]), Line(a[i], a[road[i]]), r);
            if (ccw(a[convexList[w-1].FI], a[convexList[w-1].SE], r)) {
                convexList.pop_back();
                w--;
            }
            else break;
        }
        convexList.push_back(II(i, road[i]));
    }

    // FOR(i,0,SZ(convexList)-1) cout << convexList[i].FI << ' ' << convexList[i].SE << endl;

    Point now = a[1];
    ld res = 0;
    FOR(i,1,SZ(convexList)-1) {
        Point r;
        areIntersect(Line(a[convexList[i-1].FI], a[convexList[i-1].SE]), Line(a[convexList[i].FI], a[convexList[i].SE]), r);
        res += distance(now, r);
        now = r;
    }
    res += distance(now, a[n]);
    cout << fixed << setprecision(9) << res;
    return 0;
}