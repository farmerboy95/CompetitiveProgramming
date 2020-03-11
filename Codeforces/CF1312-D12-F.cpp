/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://codeforces.com/blog/entry/74640
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
const int MAXN = 300010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;
const int K = 5;

int n, x, y, z, cnt, period;
ll a[MAXN];
typedef vector<vector<int> > state;
map<state, int> d;
vector<vector<int> > stateLog;

int mex(vector<int> q) {
    FOR(i,0,SZ(q)-1) {
        bool co = false;
        FOR(j,0,SZ(q)-1)
            if (q[j] == i) co = true;
        if (!co) return i;
    }
    return SZ(q);
}

// calculate next row using mex and push it into 5-consecutive-rows-list and pop the first one out
state moveToNextStep(state cur) {
    int f1 = mex({cur[0][K-x], cur[1][K-y], cur[2][K-z]});
    int f2 = mex({cur[0][K-x], cur[2][K-z]});
    int f3 = mex({cur[0][K-x], cur[1][K-y]});
    state nex = cur;
    nex[0].push_back(f1);
    nex[1].push_back(f2);
    nex[2].push_back(f3);
    FOR(i,0,2) nex[i].erase(nex[i].begin());
    return nex;
}

void initGrundy() {
    // map d stores every 5 consecutive rows to find the period
    d.clear();
    // current 5 consecutive rows, initially (-4, -3, -2, -1, 0)
    state cur(3, vector<int>(K, 0));
    cnt = 0;
    // stateLog stores all rows from 0 to cnt-1
    stateLog.clear();
    while (!d.count(cur)) {
        d[cur] = cnt;
        stateLog.push_back({cur[0].back(), cur[1].back(), cur[2].back()});
        cur = moveToNextStep(cur);
        cnt++;
    }
    // get period
    period = cnt - d[cur];
}

// get Grundy number of a state using the period
int getGrundy(ll k, int t) {
    if (k < cnt) return stateLog[k][t];
    int remain = cnt - period;
    k -= remain;
    return stateLog[remain + k % period][t];
}

// xorSum of other castle should be equal to Grundy number after one move on one specific castle
// to make second player lose, therefore the first one wins
int check(int u, int v) {
    return u == v;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> x >> y >> z;
        FOR(i,1,n) cin >> a[i];
        initGrundy();
        int xorSum = 0;
        FOR(i,1,n) xorSum ^= getGrundy(a[i], 0);
        int res = 0;
        FOR(i,1,n) {
            // remove castle i
            xorSum ^= getGrundy(a[i], 0);
            // check for each different first move
            res += check(xorSum, getGrundy(max(0LL, a[i]-x), 0));
            res += check(xorSum, getGrundy(max(0LL, a[i]-y), 1));
            res += check(xorSum, getGrundy(max(0LL, a[i]-z), 2));
            // recover castle i
            xorSum ^= getGrundy(a[i], 0);
        }
        cout << res << "\n";
    }
    return 0;
}
