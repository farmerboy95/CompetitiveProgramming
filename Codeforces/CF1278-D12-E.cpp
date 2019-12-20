/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Build the result from root and from right (2*n) to left (1)
        - Consider a node u, it has x childs, so that we need to put the right border of childs inside
        segment of u and left border of child to the left of segment of u
        - We find x+1 blank points from right border of u to the left of it, and put the childs to blank points
        one by one, recursively
        - Note that we should put in the increasing order of blank points because we don't want child nodes can
        connect to each other
        - Complexity O(nlog^2n)
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
const int MAXN = 500010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;
 
int n, t[MAXN*2];
vector<int> a[MAXN];
II res[MAXN];
 
void update(int u, int gt) {
    while (u <= 2*n) {
        t[u] += gt;
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
 
int getBlank(int l, int r) {
    int num = r - l + 1;
    int cnt = get(r) - get(l-1);
    return num - cnt;
}
 
void dfs(int u, int p, int r) {
    update(r, 1);
    res[u].SE = r;
 
    int cnt = SZ(a[u]);
    if (u != 1) cnt--;
    cnt++;
 
    int dau = 1, cuoi = r-1, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (getBlank(mid, r-1) >= cnt) dau = mid+1;
        else cuoi = mid-1;
    }
    update(cuoi, 1);
    res[u].FI = cuoi;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        cnt--;
        dau = cuoi+1; cuoi = r-1;
        while (dau <= cuoi) {
            mid = (dau + cuoi) >> 1;
            if (getBlank(mid, r-1) >= cnt) dau = mid+1;
            else cuoi = mid-1;
        }
        dfs(v, u, cuoi);
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }
    dfs(1, 0, 2*n);
    FOR(i,1,n) cout << res[i].FI << ' ' << res[i].SE << "\n";
    return 0;
}