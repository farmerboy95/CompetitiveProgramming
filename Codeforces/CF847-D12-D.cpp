/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - If the dog does not wait, it will reach the bowl i in i seconds, we consider that
        time as starting time, so we deduct i from a[i] to make all starting time consistent.
        - So the ending moments are also needed to be deducted by i as well. 
        - Then we just need to find the moment that the dog can eat the largest number of bowls
        of food.
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

int n, f[MAXN * 3];
ll T, a[MAXN];
vector<ll> A;

struct data {
    ll l, r;
} seg[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> T;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) {
        seg[i].l = max(0LL, a[i] - i);
        seg[i].r = T - i;
        A.push_back(seg[i].l);
        A.push_back(seg[i].r);
    }
    sort(ALL(A));
    A.resize(unique(ALL(A)) - A.begin());
    FOR(i,1,n) {
        seg[i].l = lower_bound(ALL(A), seg[i].l) - A.begin();
        seg[i].r = lower_bound(ALL(A), seg[i].r) - A.begin();
        if (seg[i].l < seg[i].r) {
            f[seg[i].l]++;
            f[seg[i].r]--;
        } 
    }
    FOR(i,1,3*n) f[i] += f[i-1];
    int res = 0;
    FOR(i,0,3*n) res = max(res, f[i]);
    cout << res;
    return 0;
}
