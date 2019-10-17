/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Sort all points by z, then y, then x
        - Get the groups of points that have the same z, then in that group, get the groups of points that have the same y,
        notice that x in these groups, x are sorted, so let's make them disappear by pair
        - If we have remaining points, for example, each y has 1 point remaining, simply pair them, do the same thing with z
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
const int MAXN = 2010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;
 
struct Point {
    ll x, y, z;
    int pos;
    Point(ll x = 0, ll y = 0, ll z = 0, int pos = 0) : x(x), y(y), z(z), pos(pos) {}
};
 
struct Vector {
    ll x, y, z;
    Vector(ll x = 0, ll y = 0, ll z = 0) : x(x), y(y), z(z) {}
};
 
Vector toVec(Point a, Point b) {
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}
 
ll dist(Point a, Point b) {
    Vector v = toVec(a, b);
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
 
bool operator< (Point a, Point b) {
    if (a.z != b.z) return a.z < b.z;
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}
 
vector<Point> a, b, c;
int n;
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        ll x, y, z;
        cin >> x >> y >> z;
        a.emplace_back(Point(x, y, z, i));
    }
    sort(ALL(a));
    FOR(i,0,n-1) {
        Point p = a[i];
        int last = n-1;
        FOR(j,i+1,n-1)
            if (a[j].z != p.z) {
                last = j-1;
                break;
            }
        int r = last;
 
        c.clear();
        FOR(j,i,r) {
            Point e = a[j];
            int last2 = r;
            FOR(k,j+1,r)
                if (a[k].y != e.y) {
                    last2 = k-1;
                    break;
                }
            
            int len2 = last2 - j + 1;
            int rr = last2;
            if (len2 % 2) {
                c.push_back(a[rr]);
                rr--;
            }
 
            for (int k = j; k <= rr; k += 2) cout << a[k].pos << ' ' << a[k+1].pos << "\n";
 
            j = last2;
        }
        if (SZ(c) % 2) {
            b.push_back(c[SZ(c)-1]);
            c.pop_back();
        }
        for (int j = 0; j < SZ(c); j+=2) cout << c[j].pos << ' ' << c[j+1].pos << "\n";
        
        i = last;
    }
 
    for (int i = 0; i < SZ(b); i+=2) cout << b[i].pos << ' ' << b[i+1].pos << "\n";
    return 0;
}