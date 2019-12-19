/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Proof is the same as https://codeforces.com/blog/entry/72243
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;
 
int n, a[MAXN], cnt[MAXN];
map<II, int> ma;
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    ll res = 0;
    FOR(i,1,n) res += a[i];
 
    int m;
    cin >> m;
    while (m--) {
        int s, t, u;
        cin >> s >> t >> u;
        II p = II(s, t);
        if (ma.count(p)) {
            if (u) {
                int x = ma[p];
                if (x) {
                    res += min(cnt[x], a[x]);
                    cnt[x]--;
                    res -= min(cnt[x], a[x]);
                }
                ma[p] = u;
                res += min(cnt[u], a[u]);
                cnt[u]++;
                res -= min(cnt[u], a[u]);
            }
            else {
                int x = ma[p];
                if (x) {
                    res += min(cnt[x], a[x]);
                    cnt[x]--;
                    res -= min(cnt[x], a[x]);
                }
                ma[p] = 0;
            }
        }
        else {
            if (u) {
                ma[p] = u;
                res += min(cnt[u], a[u]);
                cnt[u]++;
                res -= min(cnt[u], a[u]);
            }
        }
        
        cout << res << "\n";
    }
    return 0;
}
