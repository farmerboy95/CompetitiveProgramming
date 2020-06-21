/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - More or less like https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/AtCoder/R067-F.java
        - It's optimal to choose a starting restaurant x and an ending one y and go from x to y
        - The answer if one goes from x to y = sum(k=1...m, max(x<=p<=y, b[p][k])) - sum(k=x+1...y, A[k])
        - Firstly let's define ini[i] as the answer if we go from 1 to i, it can be calculated in O(n*m)
        - Then we define nxt[i][j] as the position I that b[I][j] >= b[i][j]
        - Now x = 1, we have all the answer of 1..i (1 <= i <= n), as we move x forward, we need to remove
        some records of x and replace it with records from x+1 onwards using a segment tree length n.
        Use ini[i] to init segment tree.
        - For example, column 1, x = 1, we want to move x to 2, b[1][1] is the best choice from 1 to i,
        and from i+1 onwards, there are better choices. So now what we can do is to remove b[1][1] from
        the result from 1 to i on segment tree.
        - How can we replace the max data which is deleted just now with new data? We use nxt array.
        We try to move from x+1 and update the segment tree using nxt (just like the solution in the link
        above). Each element will be used to cover the array once, each time takes us O(logn). So overall
        it takes us O(n*m*logn).
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
const int MAXN = 5010;
const int MAXM = 210;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN], b[MAXN][MAXM], Max[MAXM], nxt[MAXN][MAXM];
ll ini[MAXN], t[MAXN*8], lazy[MAXN*8];

void build(int k, int l, int r) {
    if (l > r) return;
    if (l == r) {
        t[k] = ini[l];
        return;
    }
    int m = (l + r) >> 1;
    build(k*2, l, m);
    build(k*2+1, m+1, r);
    t[k] = max(t[k*2], t[k*2+1]);
}

void lazyUpdate(int k, int l, int r) {
    if (l > r) return;
    if (lazy[k] == 0) return;
    t[k] += lazy[k];
    if (l < r) {
        lazy[k*2] += lazy[k];
        lazy[k*2+1] += lazy[k];
    }
    lazy[k] = 0;
}

ll get(int k, int l, int r, int u, int v) {
    lazyUpdate(k, l, r);
    if (l > r || r < u || v < l) return -1e18;
    if (u <= l && r <= v) return t[k];
    int m = (l + r) >> 1;
    return max(get(k*2, l, m, u, v), get(k*2+1, m+1, r, u, v));
}

void update(int k, int l, int r, int u, int v, int val) {
    lazyUpdate(k, l, r);
    if (l > r || r < u || v < l) return;
    if (u <= l && r <= v) {
        lazy[k] += val;
        lazyUpdate(k, l, r);
        return;
    }
    int m = (l + r) >> 1;
    update(k*2, l, m, u, v, val);
    update(k*2+1, m+1, r, u, v, val);
    t[k] = max(t[k*2], t[k*2+1]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,2,n) cin >> a[i];
    FOR(i,1,n) FOR(j,1,m) cin >> b[i][j];

    ll sub = 0;
    FOR(i,1,n) {
        if (i > 1) sub += a[i];
        FOR(j,1,m) {
            Max[j] = max(Max[j], b[i][j]);
            ini[i] += Max[j];
        }
        ini[i] -= sub;
    }

    build(1,1,n);
    FORE(i,n,1) {
        FOR(j,1,m) {
            nxt[i][j] = i+1;
            while (nxt[i][j] <= n && b[nxt[i][j]][j] < b[i][j]) nxt[i][j] = nxt[nxt[i][j]][j];
        }
    }

    ll res = 0;
    sub = 0;
    FOR(i,1,n) {
        if (i > 1) sub += a[i];
        res = max(res, get(1,1,n,i,n) + sub);
        FOR(j,1,m) {
            update(1,1,n,i,nxt[i][j]-1,-b[i][j]);
            int I = i+1;
            while (I <= n && b[I][j] < b[i][j]) {
                update(1,1,n,I,nxt[I][j]-1,b[I][j]);
                I = nxt[I][j];
            }
        }
    }
    cout << res;
    return 0;
}
