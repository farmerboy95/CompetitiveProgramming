/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Based on https://github.com/quangloc99/CompetitiveProgramming/blob/master/UVA/11243.cpp
        - Figure: https://github.com/farmerboy95/CompetitiveProgramming/blob/master/UVA/UVA%2011243_Figure.cpp

        - Binary search side length of the desired square
        - The square must go though 3 points, and 2 of them must lie on opposite side.
        - So we brute force 2 points u, v (distinct). If distUV < sideLength, we can extend distUV to be equal
        to sideLength (extend v from u). Now len = distUV >= sideLength = side (len, side in figure),
        here we can find 2 vectors dir1 and dir2 when we rotate vector(u,v) by angle alpha and -alpha 
        respectively (in figure). Each vector can form with u and v to create opposite sides of a square.
        (of course u lies on one side and v lies on another side).
        - Now we can check all points in the set to see if all of them lie inside the sides of the square
        using cross product.
        - Finally, find projections of all points onto side that contains u (as we may moved v at first, that's
        why we consider both (u,v) and (v,u)). Calculate the difference of min projection and max projection,
        that difference should be less than or equal to current sideLength.
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

inline int cmp(ld a, ld b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

using ftype = ld;
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
    point rotate(ftype alpha) {
        return point(x * cos(alpha) - y * sin(alpha), x * sin(alpha) + y * cos(alpha));
    }
};
point operator*(ftype a, point b) {
    return b * a;
}

// dot product
ftype dot(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

// square of length
ftype norm(point a) {
    return dot(a, a);
}

// length of vector
ld abs(point a) {
    return sqrt(norm(a));
}

// projection of vector a on b
ld proj(point a, point b) {
    return dot(a, b) / abs(b);
}

// angle between vectors
ld angle(point a, point b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}

ftype cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

ftype cross(point a, point b, point c) {
    return cross(b-a, c-a);
}

int t, n;
vector<point> a;

bool check(ld sideLength) {
    FOR(i,0,n-1)
        FOR(j,0,n-1) {
            if (i == j) continue;
            point u = a[i], v = a[j];
            ld distUV = abs(v - u);
            // extend v if distUV < sideLength
            if (cmp(distUV, sideLength) < 0) {
                v = (v - u) / distUV * sideLength + u;
                distUV = sideLength;
            }
            // this angle may be nan due to the fact that sideLength may still be a bit larger
            // than distUV because of error of float number
            ld angle = asin(sideLength / distUV);

            // consider 2 vectors
            for (auto signedAngle: {angle, -angle}) {
                point dir = (v - u).rotate(signedAngle); // vector

                // check to see if all points lie between 2 sides
                bool allInside = true;
                FOR(k,0,n-1) {
                    if (k == i || k == j) continue;
                    point p = a[k];
                    if (cross(dir, p - u) * cross(dir, v - u) < 0) allInside = false;
                    if (cross(dir, p - v) * cross(dir, u - v) < 0) allInside = false;
                }
                if (!allInside) continue;

                // find projections of all points
                ld maxProject = INT_MIN, minProject = INT_MAX;
                FOR(k,0,n-1) {
                    point p = a[k];
                    // project = length(p-u) * cos * length(dir) = real projection * length(dir)
                    ld project = dot(p - u, dir);
                    maxProject = max(maxProject, project);
                    minProject = min(minProject, project);
                }
                // should multiply sideLength by length(dir) as the diff also contains length(dir)
                if (cmp(maxProject - minProject, sideLength * abs(dir)) <= 0) return true;
            }
        }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        a.clear();
        FOR(i,1,n) {
            int u, v;
            cin >> u >> v;
            a.push_back(point(u, v));
        }
        // special case
        if (n == 1) {
            cout << "0.00\n";
            continue;
        }

        ld l = 0, r = 1000;
        FOR(i,1,100) {
            ld m = (l + r) / 2;
            if (check(m)) r = m;
            else l = m;
        }

        cout << fixed << setprecision(2) << l * l << "\n";
    }
    return 0;
}
