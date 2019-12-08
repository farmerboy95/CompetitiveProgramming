/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://img.atcoder.jp/abc147/editorial.pdf
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
typedef pair<ll, ll> II;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
ll x, d;
map<ll, vector<II> > ma;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> x >> d;
    // corner cases
    if (d == 0) {
        if (x == 0) cout << 1;
        else cout << n+1;
        return 0;
    }
    // S and T may be swapped, so D could be positive
    if (d < 0) {
        x = -x;
        d = -d;
    }
    ll l = 0, r = 0;
    // choose nothing for S
    ma[0].push_back(II(0,0));

    FOR(k,1,n) {
        // get X = x % d >= 0
        ll X = (x % d + d) % d;
        // get root of the range (k * X + I * D) % D = (k * X) % D
        ll p = X * k % d;
        ll w = x * k / d;
        // 0 + 1 + ... + (k-1) <= I <= (N - k) + (N - k + 1) + ... + (N - 1)
        l += k-1;
        r += n-k;
        if (l > r) continue;
        ma[p].push_back(II(l + w, r + w));
    }
    ll res = 0;
    FORALL(it, ma) {
        // sort all ranges and merge them together to create disjoint ranges, add them to result
        sort(ALL(it->SE));
        ll l = -1, r = -1;
        bool setLR = false;
        FOR(i,0,SZ(it->SE)-1) {
            if (!setLR) {
                l = it->SE[i].FI;
                r = it->SE[i].SE;
                setLR = true;
                continue;
            }
            if (r < it->SE[i].FI) {
                res += (r - l + 1);
                l = it->SE[i].FI;
            }
            r = max(r, it->SE[i].SE);
        }
        if (setLR) res += (r - l + 1);
    }
    cout << res;
    return 0;
}
