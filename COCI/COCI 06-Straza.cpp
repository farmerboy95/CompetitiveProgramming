/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The statement does not tell us about segments that are actually points (2 endpoints are the same).
        We can eliminate those points from our set, as it would not be included in the result anyway.
        - So our problem is to check number of groups of 3 segments (1) that their intersections create a triangle.
        - First, we put our segments into groups based on their direction vectors. So 2 segments in the same
        group can overlap or not (cannot intersect). Sample test 2 in the statement tells us about overlapping
        segments, so one segment in the group of 3 segment at (1) can be created from 2 overlapping segments.
        So we should merge those overlapping segments into one. We can do it by writing linear equations of each
        segment, then consider all segments in one group of same linear equation and merge those segments.
        - After merging segments, we have number of groups based on direction vector. So here we can simply
        choose one segment from each group (in total we have to choose 3 segments), those segments should
        intersect each other. Would they create a triangle? Not sure, because their intersection can be only
        one point. To avoid this, we can simply extract intersections and check if they are the same or not
        (remember how to compare float numbers). After checking, if those are not the same, we can tell that
        we find one case.
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
typedef pair<ld, ld> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

using ftype = ll;
struct point {
    ftype x, y;
    point() {}
    point(ftype x, ftype y) : x(x), y(y) {}
    point& operator+=(const point &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point& operator-=(const point &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point& operator*=(ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    point& operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
    point operator+(const point &t) const {
        return point(*this) += t;
    }
    point operator-(const point &t) const {
        return point(*this) -= t;
    }
    point operator*(ftype t) const {
        return point(*this) *= t;
    }
    point operator/(ftype t) const {
        return point(*this) /= t;
    }
};
point operator*(ftype a, point b) {
    return b * a;
}

bool operator< (point a, point b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

bool operator== (point a, point b) {
    return a.x == b.x && a.y == b.y;
}

struct segment {
    point l, r;
    segment(point l = point(0,0), point r = point(0,0)) : l(l), r(r) {}
};

bool operator< (segment a, segment b) {
    if (a.l == b.l) return a.r < b.r;
    return a.l < b.l;
}

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

ftype cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

ftype cross(point a, point b, point c) {
    return cross(b-a, c-a);
}

bool isIntersect(segment a, segment b) {
    ftype p = cross(a.l, a.r, b.l);
    ftype q = cross(a.l, a.r, b.r);
    if (p * q > 0) return false;
    p = cross(b.l, b.r, a.l);
    q = cross(b.l, b.r, a.r);
    if (p * q > 0) return false;
    return true;
}

struct line {
    ftype a, b, c;
    point A, B;
    line(ftype a = 0, ftype b = 0, ftype c = 0) : a(a), b(b), c(c) {}
    line(point A, point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    line(point P, ftype m) {
        a = -m; b = 1;
        c = -(a * P.x + b * P.y);
    }
    ftype f(point P) {
        return a * P.x + b * P.y + c;
    }
};

bool operator< (line a, line b) {
    if (a.a == b.a) {
        if (a.b == b.b) return a.c < b.c;
        return a.b < b.b;
    }
    return a.a < b.a;
}

bool operator== (line a, line b) {
    return a.a == b.a && a.b == b.b && a.c == b.c;
}

bool areIntersect(line l1, line l2, II &p) {
    ftype dx = l1.b*l2.c - l2.b*l1.c;
    ftype dy = l1.c*l2.a - l2.c*l1.a;
    ftype d = l1.a*l2.b - l2.a*l1.b;
    p = II((ld)dx/d, (ld)dy/d);
    return true;
}

inline int cmp(ld a, ld b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

bool isEqual(II a, II b) {
    return cmp(a.FI, b.FI) == 0 && cmp(a.SE, b.SE) == 0;
}

int n;
map<point, vector<segment> > ma;
vector<vector<segment> > a;
map<line, vector<segment> > ma2;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    int res = 0;
    // read input and create direction vector, put segment into group based on its direction vector
    FOR(i,1,n) {
        point l, r;
        cin >> l.x >> l.y >> r.x >> r.y;
        if (l.x == r.x && l.y == r.y) continue;
        if (l.x == r.x) {
            if (l.y > r.y) swap(l, r);
        }
        else if (l.x > r.x) swap(l, r);

        segment s(l, r);

        // vector u
        point u = r - l;
        // remember to handle with vector values to make sure we don't create different vector
        // values from the same vector
        ll g = gcd(abs(u.x), abs(u.y));
        u.x /= g; u.y /= g;
        if (u.x < 0) {
            u.x = -u.x;
            u.y = -u.y;
        }
        if (u.x == 0) u.y = 1;
        else if (u.y == 0) u.x = 1;

        ma[u].push_back(s);
    }

    // consider each group
    FORALL(it, ma) {
        vector<segment> vs = it->SE;

        // let's put segments in this group into another groups based on their linear equations
        ma2.clear();
        FOR(i,0,SZ(vs)-1) {
            line l = line(vs[i].l, vs[i].r);
            if (l.a < 0) {
                l.a = -l.a; l.b = -l.b; l.c = -l.c;
            }
            ll g = gcd(abs(l.a), gcd(abs(l.b), abs(l.c)));
            l.a /= g; l.b /= g; l.c /= g;
            ma2[l].push_back(vs[i]);
        }

        // now we can merge segments
        vector<segment> newVector;
        FORALL(itt, ma2) {
            vector<segment> vs2 = itt->SE;
            sort(ALL(vs2));
            segment q = vs2[0];
            FOR(i,1,SZ(vs2)-1) {
                if (q.r < vs2[i].l) {
                    newVector.push_back(q);
                    q = vs2[i];
                }
                else {
                    if (q.r < vs2[i].r) q.r = vs2[i].r;
                }
            }
            newVector.push_back(q);
        }
        a.push_back(newVector);
    }

    // we can choose 3 segments from here
    int m = SZ(a);
    FOR(i,0,m-1) {
        FOR(I,0,SZ(a[i])-1) {
            segment p = a[i][I];
            FOR(j,i+1,m-1)
                FOR(J,0,SZ(a[j])-1) {
                    segment q = a[j][J];
                    if (!isIntersect(p, q)) continue;
                    FOR(k,j+1,m-1)
                        FOR(K,0,SZ(a[k])-1) {
                            segment r = a[k][K];
                            if (!isIntersect(p, r)) continue;
                            if (!isIntersect(q, r)) continue;
                            // create linear equations from segments and get intersections
                            line l1 = line(p.l, p.r);
                            line l2 = line(q.l, q.r);
                            line l3 = line(r.l, r.r);
                            II i12, i23, i13;
                            areIntersect(l1, l2, i12);
                            areIntersect(l2, l3, i23);
                            areIntersect(l1, l3, i13);
                            // remember to check if we only have one intersection instead of 3
                            // we need a triangle, not a point
                            if (isEqual(i12, i23) && isEqual(i23, i13)) continue;
                            res++;
                        }
                }
        }
    }

    cout << res;
    return 0;
}
