/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/71740
        - We do it a bit differently here. We are going to use all n+1 rows.
        - First when compressing things, we only have one group. After proceeding a[1], we have
        2 groups, 1 group 0 and one group 1.
        - For each column j, we find the largest group and try to fill a[j] into that group if
        possible. Let M be the size of that group. There are 2 cases here:
            + a[j] < Max: we can separate it into 2 groups with: a[j] (1) and Max - a[j] (0)
            + a[j] > Max: we can separate it into 2 groups with: Max-1 (1) and 1 (0). The rest of
            1 can be filled in randomly in the rest positions, we don't need to care if those 1
            can separate the other group.
        - Here we can see that the number of groups increases by 1 for each column j. So there
        are exactly n+1 groups after n columns.
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
const int MAXN = 1010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], res[MAXN][MAXN];

void solve() {
    vector<int> b;
    b.push_back(n+1);
    FOR(j,1,n) {
        int Max = 0, pos = -1;
        FOR(i,0,SZ(b)-1)
            if (b[i] > Max) {
                Max = b[i];
                pos = i;
            }
        if (Max == 1) {
            FOR(i,1,a[j]) res[i][j] = 1;
            FOR(i,a[j]+1,n+1) res[i][j] = 0;
        } else {
            if (a[j] >= Max) {
                vector<int> c;
                int now = 0;
                int num1 = a[j] - (Max - 1);
                FOR(i,0,SZ(b)-1)
                    if (i == pos) {
                        c.push_back(Max-1);
                        int g = Max-1;
                        while (g--) res[++now][j] = 1;
                        c.push_back(1);
                        g = 1;
                        while (g--) res[++now][j] = 0;
                    } else {
                        c.push_back(b[i]);
                        int g = b[i];
                        while (g--) {
                            if (num1) {
                                res[++now][j] = 1;
                                num1--;
                            } else {
                                res[++now][j] = 0;
                            }
                        }
                    }
                b = c;
            } else {
                vector<int> c;
                int now = 0;
                FOR(i,0,SZ(b)-1)
                    if (i == pos) {
                        c.push_back(a[j]);
                        int g = a[j];
                        while (g--) res[++now][j] = 1;
                        c.push_back(Max - a[j]);
                        g = Max - a[j];
                        while (g--) res[++now][j] = 0;
                    } else {
                        c.push_back(b[i]);
                        int g = b[i];
                        while (g--) res[++now][j] = 0;
                    }
                b = c;
            }
        }
    }
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    solve();
    cout << n+1 << "\n";
    FOR(i,1,n+1) {
        FOR(j,1,n) cout << res[i][j];
        cout << "\n";
    }
    return 0;
}
