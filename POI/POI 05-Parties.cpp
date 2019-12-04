/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - From "Looking for a challenge" book
        - https://github.com/farmerboy95/CompetitiveProgramming/blob/master/POI/POI%2005-Parties-Page1.jpg
        - https://github.com/farmerboy95/CompetitiveProgramming/blob/master/POI/POI%2005-Parties-Page2.jpg
        - https://github.com/farmerboy95/CompetitiveProgramming/blob/master/POI/POI%2005-Parties-Page3.jpg
        - https://github.com/farmerboy95/CompetitiveProgramming/blob/master/POI/POI%2005-Parties-Page4.jpg
        - https://github.com/farmerboy95/CompetitiveProgramming/blob/master/POI/POI%2005-Parties-Page5.jpg
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
const int MAXN = 210;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN][MAXN], even[MAXN], active[MAXN], res[MAXN];

void solve() {
    // choose v
    int v = 1;
    while (v <= n && (even[v] || !active[v])) v++;
    if (v > n) {
        FOR(i,1,n) 
            if (active[i]) res[i] = 1;
        return;
    }

    // find all neighbors of v
    bool neighborV[MAXN];
    int cntNeighbor = 0;
    FOR(i,1,n)
        if (active[i] && a[v][i]) {
            neighborV[i] = true;
            cntNeighbor++;
        }
        else neighborV[i] = false;

    // update even array
    if (cntNeighbor % 2)
        FOR(i,1,n)
            if (neighborV[i]) even[i] = 1-even[i];
    
    // update edge array
    FOR(i,1,n)
        FOR(j,1,n)
            if (i != j && neighborV[i] && neighborV[j]) a[i][j] = 1-a[i][j];

    active[v] = false;
    solve();
    int cnt2 = 0;
    FOR(i,1,n)
        if (neighborV[i] && res[i]) cnt2++;
    if (cnt2 % 2 == 0) res[v] = 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        int k, u;
        cin >> k;
        FOR(j,1,k) {
            cin >> u;
            a[i][u] = 1;
        }
        even[i] = (k % 2 == 0);
    }
    FOR(i,1,n) active[i] = true;
    solve();
    int kq = 0;
    FOR(i,1,n) kq += res[i];
    cout << kq << "\n";
    FOR(i,1,n)
        if (res[i]) cout << i << ' ';
    return 0;
}
