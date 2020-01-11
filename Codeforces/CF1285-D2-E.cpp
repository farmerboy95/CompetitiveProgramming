/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Sort all segments in the increasing order of left border.
        - Now we will consider one segment i, we need to find out how many segments
        would be formed by list of segments from 1 -> i-1, and i+1 -> n
        - We can find number of separated segments from 1 -> i using a simple iteration
        as we have sorted all segments already, save 2 values to L[i], number of separated
        segments and the furthest right border of those segments.
        - For segments from i -> n, we can use a simple set to calculate R[i], number of separated
        segments and the furthest left border of those segments.
        - As we have to remove segment i, we need to merge results from L[i-1] and R[i+1] and
        count the number of separated segments.
        - This has an issue, furthest right border of L[i-1] may merge some of the segments of R[i+1],
        which have left border <= right border of L[i-1], we can use BIT to count, at the same time
        with the iteration used to calculate R[i].
        - Why only L[i-1], can a segment of R[i+1] merge some of the segments in the left side?
        No, because that segment needs to have left border < left border of last segment of L[i-1],
        which is a contradiction, we have already sorted all segments.
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, t[MAXN*2], N;
II L[MAXN], R[MAXN];
II a[MAXN];
set<II> s;
set<int> se;
vector<int> b;

int getPos(int u) {
    int dau = 1, cuoi = SZ(b)-1;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (b[mid] >= u) cuoi = mid-1;
        else dau = mid+1;
    }
    return dau;
}

void init() {
    // transform numbers into numbers from 1 to maximum 2*n, so that we can use BIT
    cin >> n;
    FOR(i,1,n) cin >> a[i].FI >> a[i].SE;
    sort(a+1, a+n+1);
    b.clear();
    se.clear();
    FOR(i,1,n) {
        se.insert(a[i].FI);
        se.insert(a[i].SE);
    }
    b.emplace_back(0);
    FORALL(it, se) b.emplace_back(*it);
    N = SZ(se);
    FOR(i,1,N) t[i] = 0;
    FOR(i,1,n) {
        a[i].FI = getPos(a[i].FI);
        a[i].SE = getPos(a[i].SE);
    }
}

void update(int u, int val) {
    while (u <= N) {
        t[u] += val;
        u = u + (u & (-u));
    }
}

int get(int u) {
    int res = 0;
    while (u) {
        res += t[u];
        u = u - (u & (-u));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        init();
        // calc L
        II now = II(0, 0);
        int cnt = 0;
        L[0] = II(0, 0);
        FOR(i,1,n) {
            if (a[i].FI <= now.SE) now.SE = max(now.SE, a[i].SE);
            else {
                cnt++;
                now = a[i];
            }
            L[i] = II(cnt, now.SE);
        }

        R[n+1] = II(0, 2000000000);
        s.clear();
        int res = 0;
        FORE(i,n+1,2) {
            if (i == n+1) R[i] = II(0, 2000000000);
            else {
                II now = a[i];
                // add new segment, check, remove and merge some segments in set
                while (1) {
                    set<II>::iterator it = s.lower_bound(II(now.FI, now.FI));
                    if (it == s.end()) break;
                    if (it->FI <= now.SE) {
                        now.SE = max(now.SE, it->SE);
                        update(it->FI, -1);
                        s.erase(it);
                    }
                    else break;
                }
                s.insert(now);
                update(now.FI, 1);
                R[i] = II(SZ(s), s.begin()->FI);
            }
            int calc = L[i-2].FI + R[i].FI - get(L[i-2].SE);
            res = max(res, calc);
        }
        cout << res << endl;
    }
    return 0;
}
