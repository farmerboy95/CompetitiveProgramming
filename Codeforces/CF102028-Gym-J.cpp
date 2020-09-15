/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We only care about cells that are covered by 1 or 2 carpets, as the number of covered cells
        will reduce after we remove those carpets. So we have to find the number of cells covered
        by exact k carpets (k = 1, 2).
        - Let c[i] be the number of cells that only carpet i covers, let ma[(p, q)] be the number
        of cells that only carpet p and q cover. Easy to see that the number of pairs (p, q) is at
        most m^2, the rest has value ma[(P, Q)] = 0.
        - Let cnt[i][j] is the number of carpets covering cell (i, j). This array can be calculated
        using an easy partial sum. Let sum[i][j] is the sum of indexes of carpets covering cell (i, j).
        Let squareSum[i][j] is the sum of square of indexes of carpets covering cell (i, j).
        - Now if cnt[i][j] = 1, we would definitely add 1 to c[sum[i][j]], because there is only one
        carpet there.
        - If cnt[i][j] = 2, we can form a quadratic equation Ax^2 + Bx + C = 0 to find the pair (p, q)
        here. The coefficients are A = 2, B = -2 * sum[i][j], C = sum[i][j] * sum[i][j] - squareSum[i][j]
        One can easily retrieve p, q after solving the equation. Then ma[(p, q)]++, obviously.
        - Now we have 2 cases. Case 1: The 2 carpets do not intersect, so we pick 2 carpets covering the
        most cells and get the result (doesn't matter if they do intersect, it will be covered by case 2). 
        Case 2: The 2 carpets do intersect, and the intersection is in the map. Iterate through the map 
        and get the result based on it and the b[] array as well.
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
typedef pair<ll, ll> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 1510;
const int MAXM = 300010;
const int MAXK = 16;
const int MAXQ = 200010;

int t, n, m, b[MAXM], c[MAXM];
ll sum[MAXN][MAXN], squareSum[MAXN][MAXN], cnt[MAXN][MAXN];
map<II, int> ma;

void add(ll a[MAXN][MAXN], int X1, int Y1, int X2, int Y2, ll x) {
    a[X1][Y1] += x;
    a[X2+1][Y2+1] += x;
    a[X1][Y2+1] -= x;
    a[X2+1][Y1] -= x;
}

void update(ll a[MAXN][MAXN], int x, int y) {
    a[x][y] += a[x-1][y] + a[x][y-1] - a[x-1][y-1];
}

void update(int x, int y) {
    update(sum, x, y);
    update(squareSum, x, y);
    update(cnt, x, y);
}

II solveQuadraticFormula(ll A, ll B, ll C) {
    ll sqrtDelta = (ll) sqrt(B*B - 4*A*C);
    return II((-B - sqrtDelta) / (2*A), (-B + sqrtDelta) / (2*A));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n >> m;
        FOR(i,1,n) b[i] = c[i] = 0;
        FOR(i,1,m) FOR(j,1,m) sum[i][j] = squareSum[i][j] = cnt[i][j] = 0;
        FOR(i,1,n) {
            int X1, X2, Y1, Y2;
            cin >> X1 >> X2 >> Y1 >> Y2;
            add(sum, X1, Y1, X2, Y2, i);
            add(squareSum, X1, Y1, X2, Y2, (ll) i * i);
            add(cnt, X1, Y1, X2, Y2, 1);
        }

        ma.clear();
        int covered = 0;
        FOR(i,1,m)
            FOR(j,1,m) {
                update(i,j);
                if (cnt[i][j]) covered++;
                if (cnt[i][j] == 1) {
                    b[sum[i][j]]++;
                    c[sum[i][j]]++;
                }
                else if (cnt[i][j] == 2) {
                    ll A = 2, B = -2 * sum[i][j], C = sum[i][j] * sum[i][j] - squareSum[i][j];
                    ma[solveQuadraticFormula(A, B, C)]++;
                }
            }
        
        sort(b+1, b+n+1);
        int res = covered - b[n] - b[n-1];
        FORALL(it, ma) res = min(res, covered - c[it->FI.FI] - c[it->FI.SE] - it->SE);
        cout << res << "\n";
    }
    return 0;
}
