/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Mainly from https://codeforces.com/blog/entry/74146
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Event {
    int pos, idx, end;
    Event(int pos = 0, int idx = 0, int end = 0) : pos(pos), idx(idx), end(end) {}
};

bool operator< (Event a, Event b) {
    if (a.pos == b.pos) return a.end > b.end;
    return a.pos < b.pos;
}

vector<Event> events;
int n, m, k, col[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    // create events l and r+1, sort them in ascending order of coordinate
    FOR(i,1,n) {
        int l, r;
        cin >> l >> r;
        events.push_back(Event(l, i, 0));
        events.push_back(Event(r+1, i, 1));
    }
    sort(ALL(events));

    // at one point, there will be at most k segments, so when we add segment 
    // we can find free bit and create match to this segment
    // col[i] would be the bit position that would represent our segment i in dp
    vector<bool> used(k, false);
    FOR(i,0,SZ(events)-1) {
        if (events[i].end) {
            used[col[events[i].idx]] = false;
        }
        else {
            FOR(j,0,k-1)
                if (!used[j]) {
                    used[j] = true;
                    col[events[i].idx] = j;
                    break;
                }
        }
    }

    // let's maintain dp[i][mask], where i is number of events that we already processed
    // mask is the mask of k bits, where 1 in some bit means that segment corresponding 
    // to this bit is taken.
    // we can calculate dp[i] from dp[i-1], so that we only need O(2^k) memory here.
    vector<int> dp(1 << k, -2000000000);
    dp[0] = 0;
    int pre = 0;
    FOR(i,0,SZ(events)-1) {
        vector<int> dp2(1 << k, -2000000000);
        // len is number of points from pre to events[i].pos - 1
        int len = events[i].pos - pre;
        int c = col[events[i].idx];
        // dp[mask] only has data to pre-1, so let's move data to events[i].pos-1
        FOR(mask,0,(1<<k)-1)
            if (__builtin_popcount(mask) % 2) dp[mask] += len;
        
        if (events[i].end) {
            // if we delete a segment, we must choose masks with no set bit at position c
            // would be max of itself and itself with bit c on
            FOR(mask,0,(1<<k)-1)
                if (!(mask & (1<<c))) dp2[mask] = max(dp[mask], dp[mask ^ (1<<c)]);
        }
        else {
            // if we add a segment, we must choose masks with no set bit at position c
            FOR(mask,0,(1<<k)-1) 
                if (mask & (1<<c)) dp2[mask] = dp[mask ^ (1<<c)];
                else dp2[mask] = dp[mask];
        }

        // move pre to events[i].pos, we now have data to pre-1 again
        pre = events[i].pos;
        // dp2 is now dp
        swap(dp, dp2);
    }
    // we should have no segment at the end, corresponding to mask 0
    cout << dp[0];
    return 0;
}
