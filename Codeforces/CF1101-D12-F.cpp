/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://codeforces.com/blog/entry/62602
        - Complexity O(n * (m + log(q) * log(maxfuel)))
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
const int MAXN = 410;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Truck {
    int l, r, cost, stop;
    Truck(int l = 0, int r = 0, int cost = 0, int stop = 0) : l(l), r(r), cost(cost), stop(stop) {}
};

vector<Truck> b;
int n, m, a[MAXN];

bool isOK(ll u, Truck x) {
    // with max fuel u, simply iterate through [l+1, r] to check if it's ok to travel from l to r
    // O(n)
    ll curFuel = u;
    int stop = x.stop;
    FOR(i,x.l+1,x.r) {
        ll fuel = (ll) (a[i] - a[i-1]) * x.cost;
        if (fuel > u) return false;
        if (fuel > curFuel) {
            curFuel = u;
            stop--;
        }
        curFuel -= fuel;
    }
    return stop >= 0;
}

ll getRes(Truck x) {
    // find the new result
    // log(maxfuel)
    ll dau = 0, cuoi = 2e18;
    while (dau <= cuoi) {
        ll mid = (dau + cuoi) / 2;
        if (isOK(mid, x)) cuoi = mid-1;
        else dau = mid+1;
    }
    return dau;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,m) {
        Truck x;
        cin >> x.l >> x.r >> x.cost >> x.stop;
        b.push_back(x);
    }
    // shuffle the trucks
    random_shuffle(ALL(b));

    ll res = 0;
    // O(m)
    for (Truck x : b) {
        // O(n)
        if (isOK(res, x)) continue;
        // about log(m) times calling getRes
        res = max(res, getRes(x));
    }

    cout << res;
    return 0;
}
