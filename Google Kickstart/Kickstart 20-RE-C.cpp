/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We can easily see that the kid can play all the toys in the first round without any
        trouble.
        - From the second round, when playing each toy, we need the kid to forget it to continue
        our job. Specifically, if R[i] <= sum of all other E[i], the kid would forget about the toy i.
        So the kid would cry when R[i] > sum of all other E[i], or R[i] > sum - E[i], or 
        R[i] + E[i] > sum (1).
        - So if the kid cry at a specific toy i, what should we do? We should definitely remove toy i.
        Because if we remove another toy j, sum will be reduced and (1) will still be the same.
        - So we build a segment tree to find the smallest index of R[i] + E[i] which is larger than sum.
        Need to build one binary indexed tree to calculate the result if the kid cries at toy i, which is 
        sum + E[j] (j < i and toy j is not removed).
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

struct TreeNode {
    int Max, pos;
    TreeNode(int Max = 0, int pos = 0) : Max(Max), pos(pos) {}
};

int n, E[MAXN], R[MAXN];
TreeNode t[MAXN * 4];
ll bit[MAXN];

void build(int k, int l, int r) {
    if (l > r) return;
    if (l == r) {
        t[k] = TreeNode(E[l] + R[l], l);
        return;
    }
    int m = (l + r) >> 1;
    build(k*2, l, m);
    build(k*2+1, m+1, r);
    if (t[k*2].Max >= t[k*2+1].Max) t[k] = t[k*2];
    else t[k] = t[k*2+1];
}

TreeNode get(int k, int l, int r, ll sum) {
    if (l > r) return TreeNode(-1, -1);
    if (t[k].Max <= sum) return TreeNode(-1, -1);
    if (l == r && t[k].Max > sum) return t[k];
    int m = (l + r) >> 1;
    TreeNode L = get(k*2, l, m, sum);
    if (L.Max > -1) return L;
    TreeNode R = get(k*2+1, m+1, r, sum);
    if (R.Max > -1) return R;
    return TreeNode(-1, -1);
}

void update(int k, int l, int r, int u) {
    if (l > r || r < u || u < l) return;
    if (l == r) {
        t[k] = TreeNode(-1, -1);
        return;
    }
    int m = (l + r) >> 1;
    update(k*2, l, m, u);
    update(k*2+1, m+1, r, u);
    if (t[k*2].Max >= t[k*2+1].Max) t[k] = t[k*2];
    else t[k] = t[k*2+1];
}

void updateBIT(int u, int gt) {
    while (u <= n) {
        bit[u] += gt;
        u = u + (u & (-u));
    }
}
 
ll getBIT(int u) {
    ll res = 0;
    while (u) {
        res += bit[u];
        u = u - (u & (-u));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        cin >> n;
        ll sum = 0, res = 0, del = 0;
        FOR(i,1,n) {
            cin >> E[i] >> R[i];
            sum += E[i];
        }
        build(1,1,n);
        MS(bit, 0);
        FOR(i,1,n) updateBIT(i, E[i]);
        FOR(x,1,n) {
            TreeNode tr = get(1,1,n,sum);
            if (tr.Max == -1) {
                if (res < 1e18) {
                    res = 1e18;
                    del = x-1;
                }
                break;
            }

            int pos = tr.pos;
            ll now = sum + getBIT(pos-1);
            if (now > res) {
                res = now;
                del = x-1;
            }
            sum -= E[pos];
            updateBIT(pos, -E[pos]);
            update(1,1,n,pos);
        }
        cout << del << ' ';
        if (res == 1e18) cout << "INDEFINITELY\n";
        else cout << res << "\n";
    }
    return 0;
}
