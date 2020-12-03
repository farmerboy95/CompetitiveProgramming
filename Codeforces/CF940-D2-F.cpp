/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - SQRT decomposition with updates (complexity: https://codeforces.com/blog/entry/72690)
        - https://codeforces.com/blog/entry/58033
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int block[MAXN], n, q, a[MAXN], res[MAXN], pos[MAXN], before[MAXN], after[MAXN], c[MAXN], dem[MAXN*2], num[MAXN];

struct Query {
    int l, r, t, id;
    Query(int l = 0, int r = 0, int t = 0, int id = 0) : l(l), r(r), t(t), id(id) {}
};

vector<Query> qu;
vector<int> b;

bool cmp(Query a, Query b) {
    if (block[a.l] == block[b.l]) {
        if (block[a.r] == block[b.r]) return a.t < b.t;
        return block[a.r] < block[b.r];
    }
    return block[a.l] < block[b.l];
}

void del(int u) {
    --num[dem[u]];
    ++num[--dem[u]];
}

void add(int u) {
    --num[dem[u]];
    ++num[++dem[u]];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    // pick the size of the block, should be n^(2/3) to get the best complexity
    int sz = 2154;
    // compress the array
    FOR(i,0,n-1) {
        cin >> a[i];
        b.push_back(a[i]);
        c[i] = a[i];
        // get block idx of pos i
        block[i] = i / sz;
    }
    int numQueries = 0, numUpdates = 0;
    FOR(i,1,q) {
        int ch, u, v;
        cin >> ch >> u >> v;
        if (ch == 2) {
            u--;
            numUpdates++;
            // get position, value before and after update
            pos[numUpdates] = u;
            before[numUpdates] = a[u];
            after[numUpdates] = v;
            a[u] = v;
            b.push_back(v);
        } else {
            u--; v--;
            numQueries++;
            qu.push_back(Query(u, v, numUpdates, numQueries));
        }
    }
    FOR(i,0,n-1) a[i] = c[i];

    // compress and set new array values and update values
    sort(ALL(b));
    b.erase(unique(ALL(b)), b.end());

    FOR(i,0,n-1) a[i] = lower_bound(ALL(b), a[i]) - b.begin();
    FOR(i,1,numUpdates) before[i] = lower_bound(ALL(b), before[i]) - b.begin();
    FOR(i,1,numUpdates) after[i] = lower_bound(ALL(b), after[i]) - b.begin();

    sort(ALL(qu), cmp);
    // start to move
    int L = 0, R = -1, T = 0;
    for (Query x : qu) {
        while (T > x.t) {
            if (L <= pos[T] && pos[T] <= R) {
                del(after[T]);
                add(before[T]);
            }
            a[pos[T]] = before[T];
            T--;
        }
        while (T < x.t) {
            T++;
            if (L <= pos[T] && pos[T] <= R) {
                del(before[T]);
                add(after[T]);
            }
            a[pos[T]] = after[T];
        }
        while (L > x.l) add(a[--L]);
        while (R < x.r) add(a[++R]);
        while (L < x.l) del(a[L++]);
        while (R > x.r) del(a[R--]);
        // O(sqrt(n)) here actually
        FOR(i,1,100000)
            if (!num[i]) {
                res[x.id] = i;
                break;
            }
    }

    FOR(i,1,numQueries) cout << res[i] << "\n";
    return 0;
}
