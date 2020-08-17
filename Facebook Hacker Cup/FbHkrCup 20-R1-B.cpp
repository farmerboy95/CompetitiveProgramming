/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - It's easy to see that we can binary search the result, because the bigger the needed time
        is, the higher chance we can do it.
        - Now sort the array of log cluster (q) and log driver (p) in ascending order.
        - Since s = 0, the number of log clusters that one log driver is in charge of does not matter,
        so for each log driver from 1 to n, we can use the amount of time to cover the largest number
        of log cluster that he can.
        - Let's define "last" as the minimum index of uncovered cluster, it's easy to see that we have
        to cover from "last" toward n, as it would not waste the time of the next driver to cover "last".
        - We have to find the largest cluster x that x - last + 1 is largest and the time needed to cover
        them is within the current time we are checking.
        - If last is to the right of driver i, we just go to the right until we can't go anymore due to
        the amount of time for one driver.
        - If last is to the left of driver i, first we have to check if driver i can cover last. If not,
        we return false as the next driver could not cover it as well. Otherwise, we need to find furthest x
        to the right of driver i. There are 2 ways to do:
            + Go to the left to last, then go to the right to x.
            + Go to the right to x, then go to the left to last.
        - Then we choose the way that costs smaller time, update last after finding the last x and consider
        the next driver.
        - Finally, there should be no cluster left.
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
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, k, s;
ll p[MAXN], q[MAXN];

void input() {
    ll A, B, C, D;
    cin >> n >> m >> k >> s;

    FOR(i,1,k) cin >> p[i];
    cin >> A >> B >> C >> D;
    FOR(i,k+1,n) p[i] = (A * p[i-2] + B * p[i-1] + C) % D + 1;

    FOR(i,1,k) cin >> q[i];
    cin >> A >> B >> C >> D;
    FOR(i,k+1,m) q[i] = (A * q[i-2] + B * q[i-1] + C) % D + 1;
}

void init() {
    sort(p+1, p+n+1);
    sort(q+1, q+m+1);
}

bool check(ll u) {
    int last = 1, pos = 0;
    FOR(i,1,n) {
        if (last > m) break;
        // pos is the closest log cluster to the left of driver i
        if (pos + 1 <= m && q[pos + 1] <= p[i]) pos++;

        if (p[i] >= q[last]) {
            // last is to the left of driver i
            if (p[i] - q[last] > u) return false;
            int newLast = pos+1;

            FOR(j,pos+1,m) {
                ll x = min(p[i] - q[last], q[j] - p[i]) + q[j] - q[last];
                if (x > u) break;
                newLast = j+1;
            }

            last = newLast;
        } else {
            // last is to the right of driver i
            int newLast = last;
            FOR(j,last,m) {
                ll x = q[j] - p[i];
                if (x > u) break;
                newLast = j+1;
            }
            last = newLast;
        }
    }
    return last > m;
}

ll handle() {
    ll dau = 1, cuoi = 1e15;
    while (dau <= cuoi) {
        ll mid = (dau + cuoi) / 2;
        if (check(mid)) cuoi = mid-1;
        else dau = mid+1;
    }
    return dau;
}

ll solve() {
    input();
    init();
    return handle();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        cout << solve() << "\n";
    }
    return 0;
}
