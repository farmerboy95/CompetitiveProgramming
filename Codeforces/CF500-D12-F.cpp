/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/15513
        - https://github.com/MetalBall887/Competitive-Programming/blob/master/CodeForces/CF500-D12-F.cpp
        - More comments in code
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
const int MAXN = 4010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Item {
    int c, h, t;
    Item(int c = 0, int h = 0, int t = 0) : c(c), h(h), t(t) {}
} a[MAXN];

bool operator< (Item a, Item b) {
    return a.t < b.t;
}

int n, p, posInBlock[MAXN], blockPos[MAXN];
vector<Item> block[MAXN];
vector<vector<vector<int> > > pref, suf;

vector<vector<int> > calc(int u) {
    vector<vector<int> > dp;
    if (SZ(block[u]) == 0) return dp;
    FOR(i,0,SZ(block[u])-1) dp.push_back(vector<int> (4001, 0));
    FOR(i,block[u][0].c,4000) dp[0][i] = block[u][0].h;
    FOR(i,1,SZ(block[u])-1) {
        FOR(j,0,4000) {
            dp[i][j] = dp[i-1][j];
            if (j >= block[u][i].c) dp[i][j] = max(dp[i][j], dp[i-1][j-block[u][i].c] + block[u][i].h);
        }
    }
    return dp;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> p;
    FOR(i,0,n-1) cin >> a[i].c >> a[i].h >> a[i].t;
    // sort input based on starting time t
    sort(a, a+n);

    // now we put each of the items to a block [1, p], [p+1, 2p], [2p+1, 3p] ...
    int cur = 0;
    FOR(i,0,n-1) {
        while ((cur+1) * p <= a[i].t) cur++;
        block[cur].push_back(a[i]);
        // position of the item i in the block
        posInBlock[i] = SZ(block[cur])-1;
        // block index of the item i in the block
        blockPos[i] = cur;
    }

    // now we do dp on each block, each block has dp[i][j] = the largest happiness if we
    // use at most j coins and we are considering first i items in the block
    // thus we do this with a prefix of the block and a suffix of the block
    FOR(i,0,cur) {
        pref.push_back(calc(i));
        reverse(ALL(block[i]));
        suf.push_back(calc(i));
    }

    int q;
    cin >> q;
    while (q--) {
        int t, b;
        cin >> t >> b;
        // notice that if all segment lengths are p, then from a time t, only items whose
        // segments start at [t-p+1, t] intersect the query, it would be the items with index
        // in [l, r]
        int l = lower_bound(a, a+n, Item(0, 0, t-p+1)) - a;
        int r = upper_bound(a, a+n, Item(0, 0, t)) - a - 1;

        // corner case
        if (l > r) {
            cout << 0 << "\n";
            continue;
        }

        int res = 0;

        // l, r may be in the same block or in 2 consecutive blocks
        // right one should be a prefix, left one should be a suffix when they are in 2 blocks

        auto lef = suf[blockPos[l]][SZ(block[blockPos[l]]) - 1 - posInBlock[l]];
        auto rig = pref[blockPos[r]][posInBlock[r]];

        if (blockPos[l] == blockPos[r]) {
            // in the same block, |rig----lef|
            // if l is the first one in block, we get rig[b]
            // else we get lef[b]
            if (posInBlock[l] == 0) res = rig[b];
            else res = lef[b];
        } else {
            // otherwise => lef|rig
            // divide budget between 2 blocks in linear time 
            FOR(i,0,b) res = max(res, lef[i] + rig[b-i]);
        }

        cout << res << "\n";
    }
    return 0;
}
