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
typedef pair<ll, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

// https://cp-algorithms.com/algebra/linear-diophantine-equation.html
// function part ------------------------------------------------------------------------------------

int extendedEuclid(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = extendedEuclid(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool findAnySolution(int a, int b, int c, int &x0, int &y0, int &g) {
    // not consider the case a = b = 0
    g = extendedEuclid(abs(a), abs(b), x0, y0);
    if (c % g) return false;

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shiftSolution(int &x, int &y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

int findAllSolutions(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    // Note that if a or b is 0, then the problem only has one solution. We don't consider this case here.
    int x, y, g;
    if (!findAnySolution(a, b, c, x, y, g)) return 0;
    a /= g;
    b /= g;

    int signA = a > 0 ? +1 : -1;
    int signB = b > 0 ? +1 : -1;

    shiftSolution(x, y, a, b, (minx - x) / b);
    if (x < minx) shiftSolution(x, y, a, b, signB);
    if (x > maxx) return 0;
    int lx1 = x;

    shiftSolution(x, y, a, b, (maxx - x) / b);
    if (x > maxx) shiftSolution(x, y, a, b, -signB);
    int rx1 = x;

    shiftSolution(x, y, a, b, -(miny - y) / a);
    if (y < miny) shiftSolution(x, y, a, b, -signA);
    if (y > maxy) return 0;
    int lx2 = x;

    shiftSolution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy) shiftSolution(x, y, a, b, signA);
    int rx2 = x;

    if (lx2 > rx2) swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx) return 0;
    return (rx - lx) / abs(b) + 1;
}

/*
Find the solution with minimum value of x+y
Here, x and y also need to be given some restriction, otherwise, the answer may become negative infinity.

The idea is similar to previous section: We find any solution of the Diophantine equation, 
and then shift the solution to satisfy some conditions.

Finally, use the knowledge of the set of all solutions to find the minimum:

x' = x + k * b / g,
y' = y − k * a / g.
Note that x+y change as follows:

x' + y' = x + y + k * (b / g − a / g) = x + y + k * (b − a) / g
If a<b, we need to select smallest possible value of k. 
If a>b, we need to select the largest possible value of k. 
If a=b, all solution will have the same sum x+y.
*/
// end of function part -----------------------------------------------------------------------------

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    return 0;
}
