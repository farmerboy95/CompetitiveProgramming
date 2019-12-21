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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 2010;
const int MAXM = 35;
const int MAXK = 510;
const int MAXQ = 200010;

struct Point {
    ll x, y;
    char dir;
    Point(ll x = 0, ll y = 0, char dir = 'D') : x(x), y(y), dir(dir) {}
};

int n;
vector<Point> a, b;

ll calc(ll t) {
    b.clear();
    FOR(i,0,n-1) {
        if (a[i].dir == 'D') b.emplace_back(Point(a[i].x, a[i].y - t, 'x'));
        else if (a[i].dir == 'U') b.emplace_back(Point(a[i].x, a[i].y + t, 'x'));
        else if (a[i].dir == 'L') b.emplace_back(Point(a[i].x - t, a[i].y, 'x'));
        else b.emplace_back(Point(a[i].x + t, a[i].y, 'x'));
    }
    ll xMax = b[0].x, xMin = b[0].x, yMax = b[0].y, yMin = b[0].y;
    FOR(i,1,n-1) {
        xMax = max(xMax, b[i].x);
        xMin = min(xMin, b[i].x);
        yMax = max(yMax, b[i].y);
        yMin = min(yMin, b[i].y);
    }
    return (xMax - xMin) * (yMax - yMin);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        int x, y; char c;
        cin >> x >> y >> c;
        a.emplace_back(Point(x*2, y*2, c));
    }
    ll res = 1e18;

    ll LL = 0;
    ll RR = 1e9;
    ll ML = (LL + LL + RR) / 3;
    ll MR = (LL + RR + RR) / 3;
    while ((LL != ML) && (ML != MR) && (MR != RR)) {
        if (calc(ML) > calc(MR)) LL = ML;
        else RR = MR;
        ML = (LL + LL + RR) / 3;
        MR = (LL + RR + RR) / 3;
    }

    while (LL != RR) {
        res = min(res, calc(LL));
        LL++;
    }
    res = min(res, calc(LL));

    cout << fixed << setprecision(9) << res / 4.0;
    return 0;
}
