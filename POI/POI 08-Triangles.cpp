/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2008/code/tro/prog/tro.cpp
        - For each point, make it the origin and transform other points into new points based on new origin
        - Sort new points in counter clockwise order
        - Area of triangle with one point is the origin and point a, b is abs(a.x * b.y - a.y * b.x) / 2
        - Let e = a.x * b.y - a.y * b.x
        - e > 0 when origin, a, b is in counter clockwise order, otherwise e < 0
        - Fix a, use binary search to find list of b, and use prefix sum to get sum of b.y and b.x
        - One problem here, for each point, there would be a number of points b next to (before and after) it that would have e = 0 (OA and OB form a 0 degree angle).
        We ignore those points when doing the binary search.
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
typedef pair<int, int> II;
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
const int MAXN = 20;
const int MAXM = 1000010;
const int MAXK = 110;
const int MAXQ = 200010;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
};

struct Vector {
    ll x, y;
    Vector(ll x = 0, ll y = 0) : x(x), y(y) {}
};

Vector toVec(Point a) {
    return Vector(a.x, a.y);
}

Vector toVec(Point a, Point b) {
    return Vector(b.x - a.x, b.y - a.y);
}

ll crossProduct(Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

ll dotProduct(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

ll ccw(Point a, Point b, Point c) {
    return crossProduct(toVec(a, b), toVec(a, c));
}

// sort in counter clockwise order
bool operator< (Point a, Point b) {
    if (a.y >= 0 && b.y < 0) return true;
    if (a.y < 0 && b.y >= 0) return false;
    if (a.y == 0 && b.y == 0) {
        if (a.x >= 0 && b.x < 0) return true;
        if (a.x < 0 && b.x >= 0) return false;
        return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
    }
    if (crossProduct(toVec(a), toVec(b)) == 0) return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
    return crossProduct(toVec(a), toVec(b)) > 0;
}

int n;
vector<Point> a, b;
vector<ll> sumX, sumY;
vector<int> le, ri;
ll res = 0;

ll getSum(int l, int r, Vector &root) {
    ll sumx = 0, sumy = 0;
    if (l == 0) {
        sumx = sumX[r];
        sumy = sumY[r];
    }
    else {
        sumx = sumX[r] - sumX[l-1];
        sumy = sumY[r] - sumY[l-1];
    }
    return root.x * sumy - root.y * sumx;
}

void solve() {
    sort(ALL(b));

    int N = SZ(b);
    FOR(i,0,N-1) b.emplace_back(b[i]);
    sumX.clear();
    sumY.clear();
    le.clear();
    ri.clear();
    // get prefix sum
    FOR(i,0,SZ(b)-1) {
        if (i == 0) {
            sumX.emplace_back(b[i].x);
            sumY.emplace_back(b[i].y);
        }
        else {
            sumX.emplace_back(sumX[SZ(sumX)-1] + b[i].x);
            sumY.emplace_back(sumY[SZ(sumY)-1] + b[i].y);
        }
    }
    int cnt = 1;
    int lef = 0;
    // find left side and right side of group of points that would have pairly form a 0 degree angle
    FOR(i,1,N)
        if (i != N && crossProduct(toVec(b[i-1]), toVec(b[i])) == 0 && dotProduct(toVec(b[i-1]), toVec(b[i])) > 0) {
            cnt++;
        }
        else {
            FOR(j,lef,i-1) {
                le.emplace_back(lef);
                ri.emplace_back(i-1);
            }
            cnt = 1;
            lef = i;
        }
    FOR(i,0,N-1) {
        int dau = ri[i]+1, cuoi = le[i]+N-1;
        Vector root = toVec(b[i]);
        if (dau > cuoi) continue;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) / 2;
            if (crossProduct(root, toVec(b[mid])) >= 0) dau = mid+1;
            else cuoi = mid-1;
        }
        // left side is +, right side is -
        if (cuoi >= i+1) res += getSum(i+1, cuoi, root);
        if (cuoi + 1 <= i+N-1) res -= getSum(cuoi+1, i+N-1, root);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        Point p;
        cin >> p.x >> p.y;
        a.emplace_back(p);
    }
    FOR(i,0,n-1) {
        b.clear();
        // transform other points into new points based on origin a[i]
        FOR(j,0,n-1)
            if (i != j) b.emplace_back(Point(a[j].x - a[i].x, a[j].y - a[i].y));
        solve();
    }
    res /= 6;
    if (res % 2) cout << res/2 << ".5";
    else cout << res/2 << ".0";
    return 0;
}