/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/72804
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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 2510;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
II a[MAXN];
vector<II> b;

ll ccw(II a, II b) {
    return (ll) a.FI * b.SE - (ll) b.FI * a.SE;
}

bool cmp(II a, II b) {
    bool x = a < II(0,0);
    bool y = b < II(0,0);
    if (x != y) return x < y;
    return ccw(a, b) > 0;
}

ll C(int n, int k) {
    ll res = 1;
    FOR(i,1,k) {
        res *= n - i + 1;
        res /= i;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i].FI >> a[i].SE;
    ll res = 0;
    FOR(i,1,n) {
        b.clear();
        FOR(j,1,n)
            if (i != j) b.emplace_back(II(a[j].FI - a[i].FI, a[j].SE - a[i].SE));
        sort(ALL(b), cmp);
        int k = 0;
        // good two pointer approach
        FOR(j,0,SZ(b)-1) {
            while (k < j + SZ(b) && ccw(b[j], b[k % SZ(b)]) >= 0) k++;
            res += C(k - j - 1, 3);
        }
    }
    cout << C(n, 5) * 5 - res;
    return 0;
}
