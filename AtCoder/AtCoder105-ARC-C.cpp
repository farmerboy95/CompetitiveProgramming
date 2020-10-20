/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://atcoder.jp/contests/arc105/editorial/201
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
const int MAXN = 110;
const int MAXM = 100010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN], f[MAXM], d[MAXN];
II b[MAXM];
vector<II> A[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,m) {
        int l, v;
        cin >> l >> v;
        b[i] = II(v, l);
    }

    // max(w) should be <= min(v)
    int Max = 0;
    FOR(i,1,n) Max = max(Max, a[i]);
    int Min = 1e9;
    FOR(i,1,m) Min = min(Min, b[i].FI);
    if (Max > Min) {
        cout << -1;
        return 0;
    }

    sort(a+1, a+n+1);
    sort(b+1, b+m+1);
    FOR(i,1,m) f[i] = max(f[i-1], b[i].SE);
    int res = 2e9;
    do {
        // check each permutation
        FOR(i,1,n) A[i].clear();
        FOR(i,1,n-1) {
            int sum = a[i];
            // there is a route from i to i+1 with distance = 0 in default
            A[i].push_back(II(i+1, 0));
            FOR(j,i+1,n) {
                sum += a[j];
                // find the largest v which is smaller than sum, then the largest length
                // will be the edge length from i to j
                int dau = 1, cuoi = m, mid;
                while (dau <= cuoi) {
                    mid = (dau + cuoi) >> 1;
                    if (b[mid].FI < sum) dau = mid+1;
                    else cuoi = mid-1;
                }
                int len = f[cuoi];
                A[i].push_back(II(j, len));
            }
        }
        // use dp to find the largest path from 1 to n
        MS(d, 0);
        FOR(i,1,n) {
            FOR(j,0,SZ(A[i])-1) {
                int v = A[i][j].FI;
                int c = A[i][j].SE;
                d[v] = max(d[v], d[i] + c);
            }
        }
        // get the minimum one among all permutations
        res = min(res, d[n]);
    } while (next_permutation(a+1, a+n+1));
    cout << res;
    return 0;
}
