/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/66506?#comment-505659
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, q, a[4][MAXN], Max[MAXN], D[MAXN], b[MAXN][4], laz[MAXN * 8];

// segment tree saves Min and min position of that value in segment
struct Data {
    int Min, pos;
    Data(int Min = 1000000000, int pos = 1000000000) : Min(Min), pos(pos) {}
} t[MAXN*8];

bool operator< (Data a, Data b) {
    if (a.Min != b.Min) return a.Min < b.Min;
    return a.pos < b.pos;
}

void build(int k, int l, int r) {
    if (l > r) return;
    if (l == r) {
        t[k].Min = D[l];
        t[k].pos = l;
        return;
    }
    int m = (l + r) >> 1;
    build(k*2, l, m);
    build(k*2+1, m+1, r);
    t[k] = min(t[k*2], t[k*2+1]);
}

void lazyUpdate(int k, int l, int r) {
    if (l > r) return;
    if (laz[k] == 0) return;
    t[k].Min += laz[k];
    if (l < r) {
        laz[k*2] += laz[k];
        laz[k*2+1] += laz[k];
    }
    laz[k] = 0;
}

void update(int k, int l, int r, int u, int v, int gt) {
    lazyUpdate(k,l,r);
    if (l > r || r < u || v < l) return;
    if (u <= l && r <= v) {
        laz[k] += gt;
        lazyUpdate(k,l,r);
        return;
    }
    int m = (l + r) >> 1;
    update(k*2, l, m, u, v, gt);
    update(k*2+1, m+1, r, u, v, gt);
    t[k] = min(t[k*2], t[k*2+1]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    FOR(i,1,3)
        FOR(j,1,n) {
            cin >> a[i][j];
            // store positions of a[i][j] in each array (from 1 to 3)
            b[a[i][j]][i] = j;
        }

    // get Max pos of a[i][j]
    FOR(i,1,3)
        FOR(j,1,n) Max[a[i][j]] = max(Max[a[i][j]], j);
    
    // init array D
    FOR(i,1,n) D[Max[i]]--;
    FOR(i,1,n) D[i] += D[i-1];
    FOR(i,1,n) D[i] += i;
    build(1,1,n);

    while (q--) {
        int ch, p, u, v;
        cin >> ch;
        if (ch == 1) {
            cin >> u;
            if (t[1].Min) cout << "NE\n";
            else if (Max[u] <= t[1].pos) cout << "DA\n";
            else cout << "NE\n";
        }
        else {
            cin >> p >> u >> v;
            int x1 = b[u][p], x2 = b[v][p];
            b[u][p] = x2;
            b[v][p] = x1;
            // remove old Max[u] and Max[v] (by increasing segments)
            update(1,1,n,Max[u],n,1);
            update(1,1,n,Max[v],n,1);

            Max[u] = 0; Max[v] = 0;
            FOR(i,1,3) {
                Max[u] = max(Max[u], b[u][i]);
                Max[v] = max(Max[v], b[v][i]);
            }
            
            // add new Max[u] and Max[v] (by decreasing segments)
            update(1,1,n,Max[u],n,-1);
            update(1,1,n,Max[v],n,-1);
        }
    }

    return 0;
}
