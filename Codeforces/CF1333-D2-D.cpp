/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - At each step, try to swap as many pairs as possible, then we will get the minimum number
        of steps required. We can also get maximum number of steps required. So Min <= k <= Max to have
        a result. Number of operation here will not exceed n^2
        - Again, at each step, we have a number of swaps, so we can separate it to a number of one-swap
        seconds, reduce k and Min to go to the next step.
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
const int MAXN = 3010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k;
vector<vector<int> > a, res;
string s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    cin >> s;
    s = " " + s;

    int Min = 0, Max = 0;
    FOR(i,1,n) {
        int cnt = 0;
        vector<int> sw;
        FOR(j,1,n-1)
            if (s[j] == 'R' && s[j+1] == 'L') sw.push_back(j);
        if (SZ(sw) == 0) break;
        Min++;
        for (auto j : sw) swap(s[j], s[j+1]);
        a.push_back(sw);
        Max += SZ(sw);
    }
    if (k > Max || k < Min) {
        cout << -1;
        return 0;
    }

    FOR(i,0,SZ(a)-1) {
        int diff = k - Min;
        int add = SZ(a[i]) - 1;
        int r = SZ(a[i]) - min(diff, add) - 1;
        int comp = 0;
        cout << r + 1 << ' ';
        FOR(j,0,r) cout << a[i][j] << ' ';
        comp++;
        cout << "\n";
        FOR(j,r+1,SZ(a[i])-1) {
            cout << 1 << ' ' << a[i][j] << "\n";
            comp++;
        }
        k -= comp;
        Min--;
    }
    return 0;
}
