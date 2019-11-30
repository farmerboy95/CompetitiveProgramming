/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's solve the following problem first: Given rectangles on 2d plane (Oxy), count the number of pairs of rectangles in conflict
            + We use sweep line
            + Store events (open / close rectangles) in the ascending order of x, the line will sweep from left to right
            + At each x that has the event of opening a rectangle, we need to count the number of rectangles in conflict with it which
            were considered.
            + Each event has starting point y1 and ending point y2, we would have some cases like these:
                        Considering            |-------------------|
                                  1    |-------------|
                                  2                          |-----------|
                                  3                 |---------|
                                  4     |----|
            + Should we count the number of starting points from y1 to y2? No, it would miss segment 1
            + Should we count the number of ending points from y1 to y2? No, it would miss segment 2
            + Should we count the number of starting points from 1 to y2? No, segment 4 would be counted
            + At this point, we should eliminate segments that have ending points from 1 to y1-1
            => Formula = (number of starting points from 1 to y2) - (number of ending points from 1 to y1-1)
            + We can use BIT (Fenwick tree) to solve this
        - The same thing can be applied to 3d problem
        - We would have 1000 planes Oxy (as z-coordinates are equal), more over, rectangles in Oxz planes could be in conflict
        with rectangles in Oxy planes
        => We use sweep plane (not line)
        - We would have 3 different groups of events, each for each plane that we would use for sweeping
        - For example, consider plane Oxy: 
            + We sweep by x
            + Each event will store type (1 - open a rectangle in Oxy, 2 - a rectangle in Oyz, 3 - close a rectangle in Oxy)
            + Why don't we consider rectangles in Oxz? Because rectangles in Oyz will have equal x1 and x2, so that we can sweep by x.
            + We don't consider opening and closing rectangles in Oyz, because Oyz will have its own handler, we only need to care about
            the number of rectangles in Oxy that are in conflict with that Oyz rectangle
            + Now to calculate result, do the similar thing as 2d problem, I use coordinates in Event object
                                z2  +-----------------------+
                                    |                       |
                                    |                       |
                                    |                       |
                                    |                       |
                                    |                       |
                                    |                       |
                                z1  -------------------------
                                    |***********************|
                                    |***********************|
                                    |***********************|
                                1   +-----------------------+
                                    x1                      x2
            + So Formula = (number of starting points from (x1,1) to (x2,z2)) - (number of ending points from (x1,1) to (x2,z1-1))
            + Remember to update starting points and ending points for type = 1 and 3 respectively
            + Use 2D BIT (Fenwick tree) to solve this
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
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Event {
    int type, y, x1, x2, z1, z2;
    Event(int type = 0, int y = 0, int x1 = 0, int x2 = 0, int z1 = 0, int z2 = 0) : type(type), y(y), x1(x1), x2(x2), z1(z1), z2(z2) {}
};

bool operator< (Event a, Event b) {
    if (a.y == b.y) return a.type < b.type;
    return a.y < b.y;
}

int n;
vector<Event> sweepZX, sweepXY, sweepYZ;

struct BIT2D {
    int t[MAXM + 10][MAXM + 10];

    void clear() {
        MS(t, 0);
    }

    void add(int x, int y, int gt) {
        for (int i = x; i <= MAXM; i += (i & (-i)))
            for (int j = y; j <= MAXM; j += (j & (-j))) t[i][j] += gt;
    }

    int get(int x, int y) {
        int res = 0;
        for (int i = x; i > 0; i -= (i & (-i)))
            for (int j = y; j > 0; j -= (j & (-j))) res += t[i][j];
        return res;
    }

    int query(int X1, int Y1, int X2, int Y2) {
        return get(X2, Y2) - get(X2, Y1-1) - get(X1-1, Y2) + get(X1-1, Y1-1);
    }

} lo, hi;

ll sweep(vector<Event> e) {
    sort(ALL(e));
    ll res = 0;

    lo.clear();
    hi.clear();

    FOR(i,0,SZ(e)-1) {
        if (e[i].type == 1 || e[i].type == 2) {
            res += lo.query(e[i].x1, 1, e[i].x2, e[i].z2) - hi.query(e[i].x1, 1, e[i].x2, e[i].z1-1);
        }
        if (e[i].type == 1) {
            lo.add(e[i].x1, e[i].z1, 1);
            hi.add(e[i].x2, e[i].z2, 1);
        }
        if (e[i].type == 3) {
            lo.add(e[i].x1, e[i].z1, -1);
            hi.add(e[i].x2, e[i].z2, -1);
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        int X1, Y1, Z1, X2, Y2, Z2;
        cin >> X1 >> Y1 >> Z1 >> X2 >> Y2 >> Z2;
        if (X1 > X2) swap(X1, X2);
        if (Y1 > Y2) swap(Y1, Y2);
        if (Z1 > Z2) swap(Z1, Z2);
        if (X1 == X2) {
            sweepXY.push_back(Event(1, Y1, X1, X2, Z1, Z2));
            sweepXY.push_back(Event(3, Y2, X1, X2, Z1, Z2));
            sweepZX.push_back(Event(2, X1, Z1, Z2, Y1, Y2));
        }
        else if (Y1 == Y2) {
            sweepYZ.push_back(Event(1, Z1, Y1, Y2, X1, X2));
            sweepYZ.push_back(Event(3, Z2, Y1, Y2, X1, X2));
            sweepXY.push_back(Event(2, Y1, X1, X2, Z1, Z2));
        }
        else {
            sweepZX.push_back(Event(1, X1, Z1, Z2, Y1, Y2));
            sweepZX.push_back(Event(3, X2, Z1, Z2, Y1, Y2));
            sweepYZ.push_back(Event(2, Z1, Y1, Y2, X1, X2));
        }
    }
    cout << sweep(sweepXY) + sweep(sweepYZ) + sweep(sweepZX);
    return 0;
}
