/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First, compress all h[i] into numbers from 0 to n-1 (the difference in height does not
        really matter in this problem)
        - Then for each node x, we bfs to find all heights that u can reach and save them into
        an array named f[x] or something.
        - Finally, we consider all pairs i, j (i < j), find out the LCA of each pair and calculate
        the result. (O(n^2))
        - But how to find LCA quickly? Or quickly enough?
        - If array f[x] is a boolean array, we can only put f[x][k] = 1 if we can reach height k
        from x and 0 otherwise. So it seems that this array f[x] is a binary representation of 
        a number and its length is n. We can use bitset or manually create an array of 50 with 60 bits
        for each element (60 * 50 = 3000 = MAXN)
        - We can easily see (by drawing a grid using the sample testcase) that LCA of a pair of node
        (i, j) is the position of the least significant bit of (f[i] & f[j]), note that that position
        is just the height, we should transform it back to the index of the node that has that height.
*/
 
#include <bits/stdc++.h>
#define FI first
#define SE second
#define EPS 1e-9
#define ALL(a) a.begin(), a.end()
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

int n, m, h[MAXN], rev[MAXN];
ll f[MAXN][50];
vector<int> b, a[MAXN];

ll MOD = 666013;

int get(int u) {
    int dau = 0, cuoi = SZ(b)-1;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (b[mid] >= u) cuoi = mid-1;
        else dau = mid+1;
    }
    return dau;
}

// manually set and check bit, as I'm not quite familiar with bitset
void setBit(int u, int H) {
    int pos = H / 60;
    int vt = H % 60;
    f[u][pos] |= (1LL << vt);
}

bool checkBit(int u, int H) {
    int pos = H / 60;
    int vt = H % 60;
    if (f[u][pos] & (1LL << vt)) return true;
    return false;
}

void bfs(int u) {
    queue<int> q;
    int H = h[u];
    setBit(u, H);
    q.push(u);
    while (SZ(q)) {
        int r = q.front();
        q.pop();
        FOR(i,0,SZ(a[r])-1) {
            int v = a[r][i];
            H = h[v];
            if (!checkBit(u, H)) {
                setBit(u, H);
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("casute.in", "r", stdin);
    freopen("casute.out", "w", stdout);

    // read and compress heights
    cin >> n >> m;
    FOR(i,1,n) {
        cin >> h[i];
        b.push_back(h[i]);
    }
    sort(ALL(b));
    FOR(i,1,n) {
        h[i] = get(h[i]);
        rev[h[i]] = i;
    }

    while (m--) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
    }

    FOR(i,1,n) bfs(i);

    ll res = 0;
    // the most complex part of this problem
    FOR(i,1,n)
        FOR(j,i+1,n) {
            int pos = 0;
            bool co = false;
            FOR(k,0,49) {
                ll x = (f[i][k] & f[j][k]);
                if (x) {
                    // find least significant bit, may take about O(logn)
                    x = x & (-x);
                    int g = int(log2(x));
                    pos += g;
                    co = true;
                    break;
                }
                pos += 60;
            }
            // transform height back to index
            if (!co) pos = 0;
            else pos = rev[pos];
            res = (res * (n+1) + pos) % MOD;
        }
    cout << res;
    return 0;
}
