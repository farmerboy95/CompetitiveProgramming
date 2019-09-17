/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Transform (x, y) to (X, Y) (x+y, x-y)
        - Then distance between 2 points in new space can be sum of difference of X and Y of 2 points (with some special cases about parity)
        - We can simply sort 1 dimension of point and do the calculation, then sort the other dimension and do the same thing
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
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

struct Point {
    int x, y, cs;
    Point(int x = 0, int y = 0, int cs = 0) : x(x), y(y), cs(cs) {}
};

bool operator< (Point a, Point b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

Point a[MAXN], b[MAXN];
ll res[MAXN];
int n;

Point transform(Point p) {
    return Point(p.x + p.y, p.x - p.y, p.cs);
}

void calc(int add) {
    ll sumOdd = 0, sumEven = 0, cntOdd = 0, cntEven = 0;
    FOR(i,1,n) {
        int pos = b[i].cs;
        if (b[i].x % 2) {
            res[pos] += (cntOdd * b[i].x - sumOdd) / 2;
            res[pos] += (cntEven * (b[i].x + add) - sumEven) / 2;
            sumOdd += b[i].x;
            cntOdd++;
        }
        else {
            res[pos] += (cntEven * b[i].x - sumEven) / 2;
            res[pos] += (cntOdd * (b[i].x + add) - sumOdd) / 2;
            sumEven += b[i].x;
            cntEven++;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i].x >> a[i].y;
        a[i].cs = i;
    }
    FOR(i,1,n) b[i] = transform(a[i]);

    // sort by x
    sort(b+1, b+n+1);
    calc(1);

    // calc from n to 1
    FOR(i,1,n) b[i].x = -b[i].x;
    sort(b+1, b+n+1);
    calc(1);

    // sort by y
    FOR(i,1,n) swap(b[i].x, b[i].y);
    sort(b+1, b+n+1);
    // no need to care about parity because we got that in the first dimension calculation
    calc(-1);

    // calc from n to 1
    FOR(i,1,n) b[i].x = -b[i].x;
    sort(b+1, b+n+1);
    calc(-1);

    ll kq = 1e18;
    FOR(i,1,n) kq = min(kq, res[i]);
    cout << kq;
    return 0;
}
