/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Maintain a segment tree which manage the maximum number of coastlines that cover a segment.
        - Then we can use sweep line (along the y axis), then get the maximum number of open segments.
        - But firstly, for each polygon, we need to know the which segments are open, and which ones
        are closed. We can handle that by simply see if the arbitrary point (left end or right end)
        is covered by a segment, if yes, the current segment is a closed one, otherwise it's the opened
        one.
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
typedef pair<II, II> IIII;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int N = 200000;

int n, a[MAXN], lazy[MAXN * 8], t[MAXN * 8];
vector<II> p;
vector<III> events;
vector<int> b;
map<int, int> pos;
vector<IIII> c;

void updateSmall(int k, int l, int r, int u, int v, int val) {
    if (l > r || r < u || v < l) return;
    if (u <= l && r <= v) {
        lazy[k] += val;
        return;
    }
    lazy[k*2] += lazy[k];
    lazy[k*2+1] += lazy[k];
    lazy[k] = 0;
    int m = (l + r) >> 1;
    updateSmall(k*2, l, m, u, v, val);
    updateSmall(k*2+1, m+1, r, u, v, val);
}

int get(int k, int l, int r, int u) {
    if (l > r || r < u || u < l) return 0;
    if (l == r) return lazy[k];
    lazy[k*2] += lazy[k];
    lazy[k*2+1] += lazy[k];
    lazy[k] = 0;
    int m = (l + r) >> 1;
    return get(k*2, l, m, u) + get(k*2+1, m+1, r, u);
}

void lazyUpdate(int k, int l, int r) {
    if (l > r) return;
    t[k] += lazy[k];
    if (l < r) {
        lazy[k*2] += lazy[k];
        lazy[k*2+1] += lazy[k];
    }
    lazy[k] = 0;
}

void update(int k, int l, int r, int u, int v, int val) {
    lazyUpdate(k,l,r);
    if (l > r || r < u || v < l) return;
    if (u <= l && r <= v) {
        lazy[k] += val;
        lazyUpdate(k,l,r);
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
    cin >> n;
    FOR(o,1,n) {
        int k;
        cin >> k;
        FOR(i,0,k-1) cin >> a[i];
        p.clear();
        FOR(i,0,k-1)
            if (i % 2 == 0) p.push_back(II(a[i], a[(i+1) % k]));
            else p.push_back(II(a[(i+1) % k], a[i]));
        
        // only handle coastlines that are parallel to Ox
        events.clear();
        FOR(i,0,k-1)
            if (p[i].SE == p[(i+1) % k].SE) {
                int l = min(p[i].FI, p[(i+1) % k].FI);
                int r = max(p[i].FI, p[(i+1) % k].FI) - 1;
                events.push_back(III(p[i].SE, II(l, r)));
            }
        sort(ALL(events));
        b.clear();
        FOR(i,0,SZ(events)-1) {
            b.push_back(events[i].SE.FI);
            b.push_back(events[i].SE.SE);
        }
        sort(ALL(b));
        b.resize(unique(ALL(b)) - b.begin());

        pos.clear();
        FOR(i,0,SZ(b)-1) pos[b[i]] = i;

        // check the status (open / close) of a segment
        // no need to refresh the lazy array because it will be cleared when iterating using queries (update / get)
        FOR(i,0,SZ(events)-1)
            if (get(1,0,N-1,pos[events[i].SE.FI])) {
                updateSmall(1,0,N-1,pos[events[i].SE.FI],pos[events[i].SE.SE],-1);
                c.push_back(IIII(II(events[i].FI, -1), events[i].SE));
            }
            else {
                updateSmall(1,0,N-1,pos[events[i].SE.FI],pos[events[i].SE.SE],1);
                c.push_back(IIII(II(events[i].FI, 1), events[i].SE));
            }
    }

    // now, it's time to do the real sweep line with segment tree
    MS(lazy, 0);
    sort(ALL(c));
    b.clear();
    FOR(i,0,SZ(c)-1) {
        b.push_back(c[i].SE.FI);
        b.push_back(c[i].SE.SE);
    }
    sort(ALL(b));
    b.resize(unique(ALL(b)) - b.begin());
    pos.clear();
    FOR(i,0,SZ(b)-1) pos[b[i]] = i;

    FOR(i,0,SZ(c)-1) {
        c[i].SE.FI = pos[c[i].SE.FI];
        c[i].SE.SE = pos[c[i].SE.SE];
    }
    int res = 0;
    FOR(i,0,SZ(c)-1) {
        update(1,0,N-1,c[i].SE.FI,c[i].SE.SE,c[i].FI.SE);
        // simply get max with every update
        res = max(res, t[1]);
    }
    cout << res;
    return 0;
}
