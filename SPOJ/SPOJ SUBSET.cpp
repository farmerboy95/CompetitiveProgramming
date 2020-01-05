/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: http://usaco.org/current/data/sol_subsets.html
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
vector<int> SL, SR;
vector<II> L, R;

vector<II> half(vector<int> &a) {
    vector<II> res;
    int N = SZ(a);

    FOR(mask,0,(1<<N)-1) {
        for (int submask = mask; ; submask = mask & (submask-1)) {
            int sum = 0;
            FOR(i,0,N-1)
                if (submask & (1<<i)) sum += a[i];
                else if (mask & (1<<i)) sum -= a[i];
            if (sum >= 0) res.emplace_back(II(sum, mask));
            if (submask == 0) break;
        }
    }
    sort(ALL(res));
    res.resize(unique(res.begin(), res.end()) - res.begin());
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        if (i % 2 == 0) SL.emplace_back(x);
        else SR.emplace_back(x);
    }
    L = half(SL);
    R = half(SR);
    int g = 0, h = 0;
    vector<bool> good(1<<n);
    while (g < SZ(L) && h < SZ(R)) {
        if (L[g].FI < R[h].FI) g++;
        else if (L[g].FI > R[h].FI) h++;
        else {
            int x = g, y = h;
            while (x < SZ(L) && L[x].FI == L[g].FI) x++;
            while (y < SZ(R) && R[y].FI == R[h].FI) y++;
            x--; y--;
            FOR(i,g,x)
                FOR(j,h,y) good[L[i].SE | (R[j].SE << SZ(SL))] = true;
            g = x+1;
            h = y+1;
        }
    }
    int res = 0;
    FOR(mask,1,(1<<n)-1) res += good[mask];
    cout << res;
    return 0;
}
