/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Proof is the same as here https://codeforces.com/blog/entry/72243
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;
ll deg[MAXN];
vector<int> pos, neg;
vector<III> res;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v, c;
        cin >> u >> v >> c;
        deg[u] -= c;
        deg[v] += c;
    }
    FOR(i,1,n)
        if (deg[i] > 0) pos.emplace_back(i);
        else if (deg[i] < 0) neg.emplace_back(i);
    
    int iPos = 0, iNeg = 0;
    while (1) {
        if (iPos >= SZ(pos)) break;
        if (iNeg >= SZ(neg)) break;

        int u = neg[iNeg];
        int v = pos[iPos];

        ll p = min(abs(deg[u]), deg[v]);
        res.emplace_back(III(II(u, v), p));
        deg[u] += p;
        deg[v] -= p;

        if (deg[u] == 0) iNeg++;
        if (deg[v] == 0) iPos++;
    }
    cout << SZ(res) << "\n";
    FOR(i,0,SZ(res)-1) cout << res[i].FI.FI << ' ' << res[i].FI.SE << ' ' << res[i].SE << "\n";
    return 0;
}