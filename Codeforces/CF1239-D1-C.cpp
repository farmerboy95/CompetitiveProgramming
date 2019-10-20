/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let the first moment that nobody stand in front of the tank is "now", the 
        last person who comes to the tank is "chosen"
        - If we cannot find any person i that has t[i] <= now, just find the minimum 
        time of the remaining persons, if it has more than one person that have the same
        minimum time, choose the smallest indexed one. (easy to prove)
        - Otherwise, get the minimum index in the list of person i that has t[i] <= now,
            + If this index is smaller than "chosen", this means someone realizes that all seats from his seat
            to the tank have been occupied, and he would go to the tank, that person is the one who has the
            minimum time in the above list (not the index)
            + Otherwise, just choose the person who has the minimum index above, because he would wait for
            the "chosen" one
        - Use segment tree to solve
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
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;
const int MAXX = 2000000000;
const ll MAXT = 1e16;

struct Data {
    ll t;
    int pos;
    Data(ll t = 0, int pos = 0) : t(t), pos(pos) {}
};

bool operator< (Data a, Data b) {
    if (a.t == b.t) return a.pos < b.pos;
    return a.t < b.t;
}

struct TreeNode {
    ll timeMin;
    int posMin, onlyPosMin;
    TreeNode(ll timeMin = 0, int posMin = 0, int onlyPosMin = 0) : timeMin(timeMin), posMin(posMin), onlyPosMin(onlyPosMin) {}
};

int n, f[MAXN], chosen;
ll res[MAXN], now = -1;
ll p; 
Data a[MAXN], b[MAXN];
TreeNode t[MAXN*4], t2[MAXN*4];

void combine(int k) {
    t[k].onlyPosMin = min(t[k*2].onlyPosMin, t[k*2+1].onlyPosMin);
    if (t[k*2].timeMin <= t[k*2+1].timeMin) {
        t[k].timeMin = t[k*2].timeMin;
        t[k].posMin = t[k*2].posMin;
    }
    else {
        t[k].timeMin = t[k*2+1].timeMin;
        t[k].posMin = t[k*2+1].posMin;
    }
}

void combine2(int k) {
    if (t2[k*2].timeMin <= t2[k*2+1].timeMin) {
        t2[k].timeMin = t2[k*2].timeMin;
        t2[k].posMin = t2[k*2].posMin;
    }
    else {
        t2[k].timeMin = t2[k*2+1].timeMin;
        t2[k].posMin = t2[k*2+1].posMin;
    }
}

void build(int k, int l, int r) {
    if (l > r) return;
    if (l == r) {
        t[k].timeMin = a[l].t;
        t[k].posMin = a[l].pos;
        t[k].onlyPosMin = a[l].pos;
        t2[k].timeMin = b[l].t;
        t2[k].posMin = b[l].pos;
        return;
    }
    int m = (l + r) >> 1;
    build(k*2, l, m);
    build(k*2+1, m+1, r);
    combine(k);
    combine2(k);
}

int getOnlyPosMin(int k, int l, int r, int u, int v) {
    if (l > r || r < u || v < l) return MAXX;
    if (u <= l && r <= v) return t[k].onlyPosMin;
    int m = (l + r) >> 1;
    return min(getOnlyPosMin(k*2,l,m,u,v), getOnlyPosMin(k*2+1,m+1,r,u,v));
}

TreeNode getTimePosMin(int k, int l, int r, int u, int v) {
    if (l > r || r < u || v < l) return TreeNode(MAXT, MAXX, 0);
    if (u <= l && r <= v) return t[k];
    int m = (l + r) >> 1;
    TreeNode g = getTimePosMin(k*2, l, m, u, v);
    TreeNode h = getTimePosMin(k*2+1, m+1, r, u, v);
    if (g.timeMin <= h.timeMin) return g;
    return h;
}

TreeNode getTimePosMin2(int k, int l, int r, int u, int v) {
    if (l > r || r < u || v < l) return TreeNode(MAXT, MAXX, 0);
    if (u <= l && r <= v) return t2[k];
    int m = (l + r) >> 1;
    TreeNode g = getTimePosMin2(k*2, l, m, u, v);
    TreeNode h = getTimePosMin2(k*2+1, m+1, r, u, v);
    if (g.timeMin <= h.timeMin) return g;
    return h;
}

void remove(int k, int l, int r, int u) {
    if (l > r || r < u || u < l) return;
    if (l == r) {
        t[k].timeMin = MAXT;
        t[k].posMin = MAXX;
        t[k].onlyPosMin = MAXX;
        return;
    }
    int m = (l + r) >> 1;
    remove(k*2, l, m, u);
    remove(k*2+1, m+1, r, u);
    combine(k);
}

void remove2(int k, int l, int r, int u) {
    if (l > r || r < u || u < l) return;
    if (l == r) {
        t2[k].timeMin = MAXT;
        t2[k].posMin = MAXX;
        return;
    }
    int m = (l + r) >> 1;
    remove2(k*2, l, m, u);
    remove2(k*2+1, m+1, r, u);
    combine2(k);
}

void solve(int l, int r) {
    TreeNode e = getTimePosMin(1,1,n,l,r);
    now = e.timeMin + p;
    res[e.posMin] = now;
    remove(1,1,n,f[e.posMin]);
    remove2(1,1,n,e.posMin);
    chosen = e.posMin;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> p;
    FOR(i,1,n) {
        ll x;
        cin >> x;
        a[i] = Data(x, i);
        b[i] = Data(x, i);
    }
    sort(a+1, a+n+1);
    FOR(i,1,n) f[a[i].pos] = i;

    build(1,1,n);

    now = -1;
    chosen = -1;
    FOR(o,1,n) {
        int dau = 1, cuoi = n, mid;
        while (dau <= cuoi) {
            mid = (dau + cuoi) >> 1;
            if (a[mid].t > now) cuoi = mid-1;
            else dau = mid+1;
        }
        // find persons that have time <= now
        if (cuoi >= 1 && cuoi <= n) {
            // get the minimum index
            int pos = getOnlyPosMin(1,1,n,1,cuoi);
            // if we can find minimum index
            if (pos != MAXX) {
                // if index < chosen, then get minimum time from 1 to chosen-1
                if (pos < chosen) {
                    TreeNode e = getTimePosMin2(1,1,n,1,chosen-1);

                    now += p;
                    res[e.posMin] = now;
                    remove(1,1,n,f[e.posMin]);
                    remove2(1,1,n,e.posMin);
                    chosen = e.posMin;
                }
                // otherwise, the one who comes next is the "index" one
                else {
                    now += p;
                    res[pos] = now;
                    remove(1,1,n,f[pos]);
                    remove2(1,1,n,pos);
                    chosen = pos;
                }
            }
            else {
                // choose the minimum time one in the remaining part
                solve(cuoi+1, n);
            }
        }
        else {
            // choose the minimum time one in the remaining part
            solve(cuoi+1, n);
        }
    }
    FOR(i,1,n) cout << res[i] << ' ';
    return 0;
}
