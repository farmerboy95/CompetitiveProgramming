/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First observation is that the fewer the group is, the faster the group is (only take soldiers with highest agility)
        => Use binary search
        - One can prove that if at a moment the leader is not in a segment, he should get back to his squad
        - Otherwise, he should disarm the trap at the right border of the segment
        => We can sort segments in the ascending order of left border, then descending order of right border
        - If the current position is not in a segment, move the whole squad to the nearest segment and start to disarm traps
        - After disarming a trap, if leader's position is in a segment, continue to disarm => get max right border of traps
        until the next segment does not have common point with current segment
        - Calculate time and compare with input time.
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 200010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;
 
struct Trap {
    int l, r, p;
    Trap(int l = 0, int r = 0, int p = 0) : l(l), r(r), p(p) {}
};
 
bool operator< (Trap a, Trap b) {
    if (a.l == b.l) return a.r > b.r;
    return a.l < b.l;
}
 
int n, m, k, t, a[MAXN];
Trap b[MAXN], c[MAXN];
 
bool check(int limit) {
    int N = 0;
    FOR(i,1,k)
        if (b[i].p <= limit) continue;
        else c[++N] = b[i];
    sort(c+1, c+N+1);
    
    int now = 0;
    int it = 1;
    int res = 0;
    while (it <= N) {
        res += c[it].l - now - 1;
        now = c[it].l - 1;
        int rig = c[it].r;
        while (1) {
            it++;
            if (it > N) break;
            if (c[it].l <= rig) rig = max(rig, c[it].r);
            else break;
        }
        res += 3 * (rig - now);
        now = rig;
    }
    res += m+1 - now;
    return res <= t;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k >> t;
    FOR(i,1,n) cin >> a[i];
    sort(a+1, a+n+1);
    FOR(i,1,k) {
        int l, r, p;
        cin >> l >> r >> p;
        b[i] = Trap(l, r, p);
    }
    int dau = 1, cuoi = a[n], mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (check(mid)) cuoi = mid-1;
        else dau = mid+1;
    }
    int res = 0;
    FOR(i,1,n) res += a[i] >= dau;
    cout << res;
    return 0;
}