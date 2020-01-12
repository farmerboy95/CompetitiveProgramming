/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Smallest enclosing circle is either one of followings:
            + having two points as diameter.
            + circumcircle of three points.
        - So, checking all possibilities, we can get O(n^4) solution.
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
const int MAXN = 55;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

using ftype = ld;

struct point2d {
    ftype x, y;
    point2d() {}
    point2d(ftype x, ftype y): x(x), y(y) {}
    point2d& operator+=(const point2d &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d& operator-=(const point2d &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d& operator*=(ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    point2d& operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
    point2d operator+(const point2d &t) const {
        return point2d(*this) += t;
    }
    point2d operator-(const point2d &t) const {
        return point2d(*this) -= t;
    }
    point2d operator*(ftype t) const {
        return point2d(*this) *= t;
    }
    point2d operator/(ftype t) const {
        return point2d(*this) /= t;
    }
};
point2d operator*(ftype a, point2d b) {
    return b * a;
}

struct line {
    ld a, b, c;
    point2d A, B;
    line(ld a = 0, ld b = 0, ld c = 0) : a(a), b(b), c(c) {} 
    line(point2d A, point2d B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    line(point2d P, ld m) {
        a = -m; b = 1;
        c = -((a * P.x) + (b * P.y)); 
    }
    ld f(point2d A) {
        return a*A.x + b*A.y + c;
    } 
};

int n;
point2d a[MAXN];

inline int cmp(ld a, ld b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

ftype cross(point2d a, point2d b) {
    return a.x * b.y - a.y * b.x;
}

ftype cross(point2d a, point2d b, point2d c) {
    return cross(b-a, c-a);
}

ld dist(point2d a, point2d b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool check(point2d p, ld diameter) {
    FOR(i,1,n)
        if (cmp(dist(a[i], p), diameter) > 0) return false;
    return true;
}

ld twoPointsAsDiameter(point2d A, point2d B) {
    point2d c = point2d((A.x + B.x) / 2, (A.y + B.y) / 2);
    if (check(c, dist(A, B) / 2)) return dist(A, B) / 2;
    return 1e9;
}

line createLine(point2d perpenVector, point2d p) {
    return line(perpenVector.x, perpenVector.y, -p.x * perpenVector.x - p.y * perpenVector.y);
}

bool areParallel(line l1, line l2) { return cmp(l1.a*l2.b, l1.b*l2.a) == 0; }

bool areIntersect(line l1, line l2, point2d &p) {
    if (areParallel(l1, l2)) return false; ld dx = l1.b*l2.c - l2.b*l1.c;
    ld dy = l1.c*l2.a - l2.c*l1.a;
    ld d = l1.a*l2.b - l2.a*l1.b;
    p = point2d(dx/d, dy/d);
    return true;
}

ld circumcircleOfThreePoints(point2d A, point2d B, point2d C) {
    point2d g = point2d((A.x + B.x) / 2, (A.y + B.y) / 2);
    point2d h = point2d((B.x + C.x) / 2, (B.y + C.y) / 2);
    line l1 = createLine(B-A, g);
    line l2 = createLine(C-B, h);
    point2d x;
    if (areIntersect(l1, l2, x)) {
        if (check(x, dist(x, A))) return dist(x, A);
        return 1e9;
    }
    return 1e9;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i].x >> a[i].y;
    ld res = 1e9;

    FOR(i,1,n)
        FOR(j,i+1,n) res = min(res, twoPointsAsDiameter(a[i], a[j]));
    
    FOR(i,1,n)
        FOR(j,i+1,n)
            FOR(k,j+1,n) res = min(res, circumcircleOfThreePoints(a[i], a[j], a[k]));

    cout << fixed << setprecision(9) << res;
    return 0;
}
