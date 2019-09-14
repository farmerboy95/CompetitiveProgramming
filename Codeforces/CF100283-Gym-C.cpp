/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - At each second, for each position (i,j), calculate number of thieves that would be asked by other thieves to get treasure.
        - More formally, let a[t][i][j] = sum(a[t+1][u][v]) (the distance between (u, v) and (i, j) is smaller than t) (t >= 1, t is the remaining time)
        - Result would be sum(a[1][i][j] * gold[i][j])

        - First, at each second k, calculate a[k][1][1], then move it right or down, add and subtract corresponding boundary diamond shape of it.
        - Use prefix sum to get diagonal sum.
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
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

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

int t, n, m, s;
ll a[MAXN][MAXN], gold[MAXN][MAXN], b[MAXN][MAXN], sum[2][MAXN*2][MAXN];

void init() {
    int x, y;
    cin >> n >> m >> s >> x >> y;
    FOR(i,1,n) FOR(j,1,m) cin >> gold[i][j];
    FOR(i,1,n) FOR(j,1,m) a[i][j] = 0;
    a[x][y] = 1;
}

ll get(int arrNum, int u, int l, int r) {
    if (u < 1 || u > n+m) return 0;
    l = max(l, 1);
    r = min(r, m);
    if (l > r) return 0;
    return (sum[arrNum][u][r] - sum[arrNum][u][l-1] + MODBASE) % MODBASE;
}

bool isInside(int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= m;
}

/* get all elements that have Manhattan distance from # to X (i, j) is k, and this diamond shape is above X
..#..
.#.#.
#.X.#
.....
.....
*/
ll getUpperSum(int i, int j, int k) {
    int lef = j - k;
    int rig = j + k;
    ll res = (get(0, i+lef, lef, j) + get(1, i-rig+m, j, rig)) % MODBASE;
    if (isInside(i-k, j)) res = (res - a[i-k][j] + MODBASE) % MODBASE;
    return res;
}

/* get all elements that have Manhattan distance from # to X (i, j) is k, and this diamond shape is below X
.....
.....
#.X.#
.#.#.
..#..
*/
ll getLowerSum(int i, int j, int k) {
    int lef = j - k;
    int rig = j + k;
    ll res = (get(1, i-lef+m, lef, j) + get(0, i+rig, j, rig)) % MODBASE;
    if (isInside(i+k, j)) res = (res - a[i+k][j] + MODBASE) % MODBASE;
    return res;
}

/* get all elements that have Manhattan distance from # to X (i, j) is k, and this diamond shape is to the left of X
..#..
.#...
#.X..
.#...
..#..
*/
ll getLeftSum(int i, int j, int k) {
    int upp = i - k;
    int low = i + k;
    ll res = (get(0, upp+j, j-k, j) + get(1, low-j+m, j-k, j)) % MODBASE;
    if (isInside(i, j-k)) res = (res - a[i][j-k] + MODBASE) % MODBASE;
    return res;
}

/* get all elements that have Manhattan distance from # to X (i, j) is k, and this diamond shape is to the right of X
..#..
...#.
..X.#
...#.
..#..
*/
ll getRightSum(int i, int j, int k) {
    int upp = i - k;
    int low = i + k;
    ll res = (get(1, upp-j+m, j, j+k) + get(0, low+j, j, j+k)) % MODBASE;
    if (isInside(i, j+k)) res = (res - a[i][j+k] + MODBASE) % MODBASE;
    return res;
}

void solve() {
    FORE(k,s-1,1) {

        // get prefix sum of all diagonal lines
        FOR(i,1,n+m) FOR(j,0,m) sum[0][i][j] = sum[1][i][j] = 0;
        FOR(i,1,n)
            FOR(j,1,m) {
                sum[0][i+j][j] = a[i][j];
                sum[1][i-j+m][j] = a[i][j];
            }

        FOR(i,1,n+m) {
            FOR(j,1,m) {
                sum[0][i][j] = (sum[0][i][j] + sum[0][i][j-1]) % MODBASE;
                sum[1][i][j] = (sum[1][i][j] + sum[1][i][j-1]) % MODBASE;
            }
        }

        // calc b[1][1]
        b[1][1] = 0;
        FOR(u,-k,k) {
            int remain = k - abs(u);
            FOR(v,-remain,remain) {
                if (!isInside(u+1, v+1)) continue;
                b[1][1] = (b[1][1] + a[u+1][v+1]) % MODBASE;
            }
        }
        
        // calc all other position of array b
        FOR(i,1,n)
            FOR(j,1,m) {
                if (i == 1 && j == 1) continue;
                if (i > 1) {
                    b[i][j] = ((b[i-1][j] - getUpperSum(i-1, j, k) + MODBASE) % MODBASE + getLowerSum(i, j, k)) % MODBASE;
                }
                else {
                    b[i][j] = ((b[i][j-1] - getLeftSum(i, j-1, k) + MODBASE) % MODBASE + getRightSum(i, j, k)) % MODBASE;
                }
            }
        
        // move array b to a
        FOR(i,1,n)
            FOR(j,1,m) a[i][j] = b[i][j];
    }

    // calc result
    ll res = 0;
    FOR(i,1,n)
        FOR(j,1,m) res = (res + gold[i][j] * a[i][j] % MODBASE) % MODBASE;
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("treasures.in", "r", stdin);
    cin >> t;
    FOR(o,1,t) {
        cout << "Case " << o << ": ";
        init();
        solve(); 
    }
    return 0;
}
