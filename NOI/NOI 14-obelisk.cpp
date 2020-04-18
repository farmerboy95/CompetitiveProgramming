/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let d[i][j] = shortest path to reach point jth on floor i
        - Imagine there is floor 0, it has only one point (Sx, Sy). There is floor N, it
        has only one point (Ex, Ey)
        - So d[i][k] = min(d[i][k], d[i-1][j] + distance from point jth of floor i-1 to point
        k of floor i)
        - So the problem reduces to how to find distance from vertical obelisk at one point
        to another point on 2d coordinate with the same state (vertical obelisk)
        - Let those 2 points are (x, y) and (u, v), we can reduce it to (0, 0) and (abs(x-u),
        abs(y-v)) because of symmetry.
        - If M == 1, the distance is simply Manhattan distance. Otherwise, it's quite complicated
        - Let M == 5, we care about the points with "x" below
                            xxxxxxxxxxxxx
                            x.....x.....x
                            x.....x.....x
                            x.....x.....x
                            x.....x.....x
                            xxxxxxXxxxxxx
                            x.....x.....x
                            x.....x.....x
                            x.....x.....x
                            x.....x.....x
                            xxxxxxxxxxxxx
        - "X" is our starting point, at those "x" points (with x % (m+1) == 0 or y % (m+1) == 0), 
        we canmanually get the distance by ourselves. If the destination is too far, we can go 
        closer to it, in the square that contains x on border (in goCloser function).
        - If our destination is on ".", we have to go to one of the "x" points and go back to
        our starting point from x, there are quite a lot of cases for this, but generally it
        is just to lay the obelisk down and roll it to "x" row or column (may refer to the code).
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
const int MAXN = 510;
const int MAXM = 110;
const int MAXK = 16;
const int MAXQ = 200010;

int N, M;
vector<II> a[MAXN];
ll d[MAXN][MAXM];

ll sameLine(int x, int m) {
    return min(x + 2, m+1 - x + 4);
}
 
ll check(int x, int y, int m) {
    if (x == 0 && y == 0) return 0;
    if (x == m+1 && y == m+1) return 4;
    if (x == m+1 && y == 0) return 2;
    if (y == m+1 && x == 0) return 2;
    if (x == 0 || x == m+1) return sameLine(y, m);
    // if (y == 0 || y == m+1) 
    return sameLine(x, m);
}

void goCloser(int &x, ll &res, int m) {
    if (x % (m+1)) {
        res += 2 * (x / (m+1));
        x %= (m+1);
    }
    else {
        if (x) {
            res += 2 * (x / (m+1) - 1);
            x = m+1;
        }
    }
}

ll solve(int x, int y, int m) {
    x = abs(x); y = abs(y);
    ll res = 0;
    goCloser(x, res, m);
    goCloser(y, res, m);
    return res + check(x, y, m);
}
 
ll dist(int x, int y, int u, int v, int m) {
    x -= u;
    y -= v;
    x = abs(x); y = abs(y);
    if (m == 1) return x + y;
    if (x % (m+1) == 0 || y % (m+1) == 0) return solve(x, y, m);

    // general case
    ll res = 1e18;
    u = x % (m+1); v = y % (m+1);
    res = min(res, u + 2 + solve(x-u, y, m));
    res = min(res, u + 2 + solve(x-u, y-(m+1), m));
    res = min(res, u + 2 + solve(x-u, y+(m+1), m));
    res = min(res, v + 2 + solve(x, y-v, m));
    res = min(res, v + 2 + solve(x-(m+1), y-v, m));
    res = min(res, v + 2 + solve(x+(m+1), y-v, m));
    u = m+1 - u; v = m+1 - v;
    res = min(res, u + 2 + solve(x+u, y, m));
    res = min(res, u + 2 + solve(x+u, y-(m+1), m));
    res = min(res, u + 2 + solve(x+u, y+(m+1), m));
    res = min(res, v + 2 + solve(x, y+v, m));
    res = min(res, v + 2 + solve(x-(m+1), y+v, m));
    res = min(res, v + 2 + solve(x+(m+1), y+v, m));
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int x, y;
    cin >> N >> M;
    cin >> x >> y;
    a[0].push_back(II(x, y));
    cin >> x >> y;
    a[N].push_back(II(x, y));
 
    FOR(i,1,N-1) {
        int k;
        cin >> k;
        while (k--) {
            cin >> x >> y;
            a[i].push_back(II(x, y));
        }
    }
 
    FOR(i,0,505) FOR(j,0,100) d[i][j] = 1e18;
    d[0][0] = 0;
 
    FOR(i,1,N)
        FOR(j,0,SZ(a[i-1])-1)
            FOR(k,0,SZ(a[i])-1) d[i][k] = min(d[i][k], d[i-1][j] + dist(a[i-1][j].FI, a[i-1][j].SE, a[i][k].FI, a[i][k].SE, M));
    
    cout << d[N][0];
    return 0;
}
