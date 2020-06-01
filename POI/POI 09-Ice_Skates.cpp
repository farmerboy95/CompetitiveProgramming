/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let A[i] is the number of skaters with foot size i
        - The key observation is that, an assignment is possible iff for all pairs (L, R)
        where 1 <= L <= R <= n - d, A[L] + A[L+1] + A[L+2] + ... + A[R] <= (R - L + 1 + d) * k.
        <=> (A[L] - k) + (A[L+1] - k) + (A[L+2] - k) + ... + (A[R] - k) <= d * k
        - So for each assignment, we can find the maximum subarray sum of A, then compare with d * k
        to print out the result.
        - Here we can use a segment tree, each node in a tree stores the following information:
            + Sum of the whole segment (val)
            + Max sum of the prefix of the segment (pre)
            + Max sum of the suffix of the segment (suf)
            + Max sum of a subarray of the segment (Max)
        - First we assign -k to each element of the array and build segment tree. Then for each
        event, we can add or subtract the number of skaters with foot size r by x. Get root.Max,
        compare with k*d and print out the result.
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

int N, M, K, D;

struct Data {
    ll val, pre, suf, Max;
    Data(ll val = 0, ll pre = 0, ll suf = 0, ll Max = 0) : val(val), pre(pre), suf(suf), Max(Max) {}
};

Data t[MAXN * 4];

void build(int k, int l, int r) {
    if (l > r) return;
    if (l == r) {
        t[k].Max = t[k].pre = t[k].suf = 0;
        t[k].val = -K;
        return;
    }
    int mid = (l + r) >> 1;
    build(k*2, l, mid);
    build(k*2+1, mid+1, r);
    t[k].val = t[k*2].val + t[k*2+1].val;
    t[k].pre = max(t[k*2].pre, t[k*2].val + t[k*2+1].pre);
    t[k].suf = max(t[k*2+1].suf, t[k*2+1].val + t[k*2].suf);
    t[k].Max = max(t[k].val, max(t[k].pre, t[k].suf));
    t[k].Max = max(t[k].Max, max(t[k*2].Max, t[k*2+1].Max));
    t[k].Max = max(t[k].Max, t[k*2].suf + t[k*2+1].pre);
}

void update(int k, int l, int r, int u, int val) {
    if (l > r || r < u || u < l) return;
    if (l == r) {
        t[k].val += val;
        t[k].Max = t[k].pre = t[k].suf = max(0LL, t[k].val);
        return;
    }
    int mid = (l + r) >> 1;
    update(k*2, l, mid, u, val);
    update(k*2+1, mid+1, r, u, val);
    t[k].val = t[k*2].val + t[k*2+1].val;
    t[k].pre = max(t[k*2].pre, t[k*2].val + t[k*2+1].pre);
    t[k].suf = max(t[k*2+1].suf, t[k*2+1].val + t[k*2].suf);
    t[k].Max = max(t[k].val, max(t[k].pre, t[k].suf));
    t[k].Max = max(t[k].Max, max(t[k*2].Max, t[k*2+1].Max));
    t[k].Max = max(t[k].Max, t[k*2].suf + t[k*2+1].pre);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> N >> M >> K >> D;
    build(1,1,N);
    FOR(i,1,M) {
        int r, x;
        cin >> r >> x;
        update(1,1,N,r,x);
        if (t[1].Max > (ll) D * K) cout << "NIE\n";
        else cout << "TAK\n";
    }
    return 0;
}
