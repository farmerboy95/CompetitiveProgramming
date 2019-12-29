/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Choose k+1 random elements, query every subset of them, number of times x that we get the minimum 
        number is k + 1 - m => m = k+1 - x
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
const int MAXN = 510;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k, a[MAXN];
vector<int> q, q2;
map<int, int> ma;

II query(vector<int> &q) {
    cout << "?";
    FOR(i,0,SZ(q)-1) cout << " " << q[i];
    cout << endl;
    int u, v;
    cin >> u >> v;
    return II(u, v);
}

void solve() {
    FOR(i,0,k) {
        q2.clear();
        FOR(j,0,k)
            if (j != i) q2.emplace_back(q[j]);
        II r = query(q2);
        ma[r.SE]++;
    }
    int x = ma.begin()->SE;
    cout << "! " << k + 1 - x << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,k+1) q.emplace_back(i);
    solve();
    return 0;
}
