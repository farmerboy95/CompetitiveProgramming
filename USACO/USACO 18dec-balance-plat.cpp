/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as editorial: http://usaco.org/current/data/sol_balance_platinum_dec18.html
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
const int MAXN = 100010;
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

int n, l[MAXN], r[MAXN];
ll f[MAXN];
vector<point2d> a;
vector<int> hull;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    cin >> n;
    FOR(i,1,n) cin >> f[i];
    // The key insight is to visualize this problem on a 2D coordinate axis.
    // If we plot each point as (k,f(k)), then this process will give us the upper convex hull 
    // of all these points. Taking into the properties of convex hulls, it becomes more clear 
    // that this process always gives the correct answer: the value of f∗(k) for any k is always 
    // equal to the weighted average of points within the hull, and so this value must also be within 
    // the upper hull.
    a.push_back(point2d(0, 0));
    FOR(i,1,n) a.push_back(point2d(i, f[i]));
    a.push_back(point2d(n+1, 0));

    // get the upper hull using favorite convex hull algorithm
    hull.push_back(0); 
    hull.push_back(1); 
    FOR(i,2,SZ(a)-1) {
        hull.push_back(i);
        while (SZ(hull) >= 3 && cross(a[hull[SZ(hull)-3]], a[hull[SZ(hull)-2]], a[hull[SZ(hull)-1]]) >= 0) hull.erase(hull.end()-2);
    }

    // we need to calculate the height of points that are not included in convex hull,
    // here we store l[i], r[i] means the nearest point in the convex hull to the left of point i
    // and to the right of point i, respectively.
    FOR(j,0,SZ(hull)-2) {
        FOR(i,hull[j]+1,hull[j+1]-1) {
            l[i] = hull[j];
            r[i] = hull[j+1];
        }
        l[hull[j]] = r[hull[j]] = hull[j];
    }
    l[n+1] = r[n+1] = n+1;

    // finally we calculate the answer, one can easily find the below formula
    FOR(i,1,n)
        if (l[i] == r[i]) cout << 100000LL * f[i] << "\n";
        else cout << (100000ULL*((r[i]-i)*f[l[i]] + (i-l[i])*f[r[i]])) / (r[i]-l[i]) << '\n';
    return 0;
}
