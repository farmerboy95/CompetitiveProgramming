/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2020/qualification-round/problems/C
    Status: AC
    Idea:
        - This is kinda different from the official solution as I did not notice the first observation.
        - So here I consider 2*n segments, as one tree can fall to the left or to the right.
        - Note that as the l, r are in [-10^9, 10^9], we need to reduce them to iterable position.
        - Now let's define dp[i] as the longest combined interval that ends at pos i, dp2[i] as the
        second longest one that ends at pos i (with the index of the last segment).
        - We also need to store events at l to update dp.
        - Now let's iterate position from left to right, at each segment, we check dp[i] to see if
        the index of dp[i] is the same as the index of the current segment. If it is, we update
        dp using dp2[i] as the indexes are surely different now.
        - Complexity O(NlogN)
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
const int MAXN = 2500010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Segment {
    int l, r, cs;
    Segment(int l, int r, int cs) : l(l), r(r), cs(cs) {}
};

int t, n;
II dp[MAXN], dp2[MAXN];
vector<Segment> a;
vector<II> open[MAXN];
vector<int> b;

int get(int u) {
    int dau = 0, cuoi = SZ(b)-1;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (b[mid] >= u) cuoi = mid-1;
        else dau = mid + 1;
    }
    return dau;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n;
        a.clear();
        b.clear();
        FOR(i,1,n) {
            int p, h;
            cin >> p >> h;
            a.push_back(Segment(p-h, p, i));
            a.push_back(Segment(p, p+h, i));
        }
        // reduce position
        for (Segment x : a) {
            b.push_back(x.l);
            b.push_back(x.r);
        }
        sort(ALL(b));
        b.resize(unique(ALL(b)) - b.begin());

        FOR(i,0,SZ(a)-1) {
            a[i].l = get(a[i].l);
            a[i].r = get(a[i].r);
        }

        FOR(i,0,SZ(b)-1) {
            open[i].clear();
            dp[i] = dp2[i] = II(0, -1);
        }

        FOR(i,0,SZ(a)-1) open[a[i].l].push_back(II(a[i].r, a[i].cs));
        
        FOR(i,0,SZ(b)-1) {
            FOR(j,0,SZ(open[i])-1) {
                int cs = open[i][j].SE;
                int rig = open[i][j].FI;
                int range = b[rig] - b[i];

                int newDp = 0;
                if (dp[i].SE != cs) newDp = dp[i].FI + range;
                else newDp = dp2[i].FI + range;

                if (newDp > dp[rig].FI) {
                    dp2[rig] = dp[rig];
                    dp[rig] = II(newDp, cs);
                }
                else if (newDp > dp2[rig].FI) dp2[rig] = II(newDp, cs);
            }
        }

        int res = 0;
        FOR(i,0,SZ(b)-1) res = max(res, dp[i].FI);
        cout << res << "\n";
    }
    return 0;
}
