/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use Divide and Conquer (Static Range Query): https://usaco.guide/plat/DC-SRQ
        - Can be solved using RMQ.
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Data {
    int l, r, pos;
    Data(int l = 0, int r = 0, int pos = 0) : l(l), r(r), pos(pos) {}
};

int n, m, a[MAXN], res[MAXN], minL[MAXN], minR[MAXN];

void solve(int l, int r, vector<Data> &b) {
    if (SZ(b) == 0 || l > r) return;
    if (l == r) {
        for (Data x : b) res[x.pos] = a[x.l];
        return;
    }
    int mid = (l+r) >> 1;

    minL[mid+1] = minR[mid] = 1000000001;

    FORE(i,mid,l) minL[i] = min(minL[i+1], a[i]);
    FOR(i,mid+1,r) minR[i] = min(minR[i-1], a[i]);

    vector<Data> L, R;
    for (Data x : b) {
        if (x.r <= mid) L.push_back(x);
        else if (x.l > mid) R.push_back(x);
        else res[x.pos] = min(minL[x.l], minR[x.r]);
    }
    if (l <= mid && SZ(L))  solve(l, mid, L);
    if (r >= mid+1 && SZ(R)) solve(mid+1, r, R);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int q;
    cin >> n >> q;
    FOR(i,1,n) cin >> a[i];
    vector<Data> b;
    FOR(i,1,q) {
        int u, v;
        cin >> u >> v;
        b.push_back(Data(u, v, i));
    }
    solve(1,n,b);
    FOR(i,1,q) cout << res[i] << "\n";
    return 0;
}
