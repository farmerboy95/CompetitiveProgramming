/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Sort all segments
        - For each segment, consider all segments that have right border inside the current segment,
        use DSU to check, if the union creates cycle => NO
        - If we merge n-1 edges => YES, otherwise => NO
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
 
int n, t[MAXN*2], lab[MAXN];
int l[MAXN*2];
vector<II> a;
 
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
 
int getRoot(int u) {
    while (lab[u] > 0) u = lab[u];
    return u;
}
 
int unionPair(int u, int v) {
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[v] = u;
        lab[u] = x;
        return u;
    }
    else {
        lab[u] = v;
        lab[v] = x;
        return v;
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        II p;
        cin >> p.FI >> p.SE;
        a.emplace_back(p);
        lab[i] = -1;
    }
    sort(ALL(a));
 
    int num = 0;
    FOR(i,0,n-1) {
        int p = get(a[i].SE);
        int h = p - get(a[i].FI);
        int now = a[i].FI;
        int U = getRoot(i+1);
        FORE(j,h,1) {
            int dau = now, cuoi = a[i].SE, mid;
            while (dau <= cuoi) {
                mid = (dau + cuoi) >> 1;
                if (p - get(mid) < j) cuoi = mid-1;
                else dau = mid+1;
            }
            int V = getRoot(l[dau]);
            
            if (U == V) {
                cout << "NO\n";
                return 0;
            }
 
            U = unionPair(U, V);
            now = dau;
        }
        update(a[i].SE, 1);
        l[a[i].SE] = i+1;
        num += h;
    }
    if (num == n-1) cout << "YES";
    else cout << "NO";
    return 0;
}