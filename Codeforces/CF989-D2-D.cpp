/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Same as https://codeforces.com/blog/entry/59968
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

int n, l, w;
vector<int> pos, neg;

// return x = the largest integer that is smaller than or equal to a / b
int divFloor(ll a, int b) {
    if (b == 0) {
        if (a > 0) return 2e9;
        return -2e9;
    }
    if (a % b < 0) a -= (b + a % b);
    return a / b;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> l >> w;
    FOR(i,1,n) {
        int x, y;
        cin >> x >> y;
        if (y == 1) pos.push_back(x);
        else neg.push_back(x);
    }
    sort(ALL(pos));
    sort(ALL(neg));

    ll res = 0;

    for (int v : neg) {
        auto barrier = lower_bound(ALL(pos), -v-l);

        // we add -1 to make the divFloor surely smaller than the intended fraction
        int g = divFloor((ll) (v + l) * (w + 1) - 1, w - 1);
        int h = divFloor((ll) (v + l) * (w - 1) - 1, w + 1);

        res += upper_bound(pos.begin(), barrier, g) - pos.begin();
        res += upper_bound(barrier, pos.end(), min(v-1, h)) - barrier;
        // I think v should be deducted by one to be surely smaller than the min() part
    }

    cout << res;
    return 0;
}
