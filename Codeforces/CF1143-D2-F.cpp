/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - y = x^2 + bx + c <=> y - x^2 = bx + c
        => (x, y) => (x, y - x^2) => Parabolas turn into lines
        - The problem is reduced to constructing a top part of convex hull on the 
        obtained points and calculate the number of segments on it.
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

using ftype = long long;
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

point2d operator*(ll a, point2d b) {
    return b * a;
}

ftype dot(point2d a, point2d b) {
    return a.x * b.x + a.y * b.y;
}

ftype norm(point2d a) {
    return dot(a, a);
}

ftype cross(point2d a, point2d b) {
    return a.x * b.y - a.y * b.x;
}

ftype cross(point2d a, point2d b, point2d c) {
    return cross(b-a, c-a);
}

vector<point2d> ch, upper, lower, A;
int n;

bool leftLower(point2d a, point2d b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x; 
}

void convexHull(vector<point2d> &a) {
    // return clockwised convex hull 
    ch.clear();
    upper.clear();
    lower.clear();
    if (SZ(a) <= 3) { 
        FOR(i,0,SZ(a)-1) ch.push_back(a[i]); 
        if (SZ(ch) == 3) {
            if (cross(ch[0], ch[1], ch[2]) > 0) reverse(ALL(ch));
            else if (cross(ch[0], ch[1], ch[2]) == 0) ch.pop_back(); 
        }
        return; 
    }
    sort(ALL(a), leftLower);
    upper.push_back(a[0]); 
    upper.push_back(a[1]); 
    FOR(i,2,SZ(a)-1) {
        upper.push_back(a[i]);
        while (SZ(upper) >= 3 && cross(upper[SZ(upper)-3], upper[SZ(upper)-2], upper[SZ(upper)-1]) >= 0) upper.erase(upper.end()-2);
    }
    FOR(i,0,SZ(upper)-1) ch.push_back(upper[i]); 
    lower.push_back(a[SZ(a)-1]); 
    lower.push_back(a[SZ(a)-2]); 
    FORE(i,SZ(a)-3,0) {
        lower.push_back(a[i]);
        while (SZ(lower) >= 3 && cross(lower[SZ(lower)-3],  lower[SZ(lower)-2], lower[SZ(lower)-1]) >= 0) lower.erase(lower.end()-2);
    }
    FOR(i,1,SZ(lower)-2) ch.push_back(lower[i]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        ll x, y;
        cin >> x >> y;
        // transform
        A.push_back(point2d(x, y - x*x));
    }
    // find convex hull
    convexHull(A);
    // corner cases
    if (SZ(ch) == 1) {
        cout << 0;
        return 0;
    }
    if (SZ(ch) == 2) {
        if (ch[0].x == ch[1].x) cout << 0;
        else cout << 1;
        return 0;
    }

    
    int res = 0;
    FOR(i,0,SZ(ch)-1) {
        point2d now = ch[i], nex = ch[(i+1) % SZ(ch)], nex2 = ch[(i+2) % SZ(ch)];
        // not considering vertical lines
        if (now.x == nex.x) continue;
        // consider segments from left to right, if a random point of convex hull is on the
        // left side of segment, it's not the line that we need
        if (now.x > nex.x) swap(now, nex);
        if (cross(now, nex, nex2) < 0) res++;
    }
    cout << res;
    return 0;
}
