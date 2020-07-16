/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's use binary search here, we check if we can achieve a score "threshold", because
        the smaller the threshold is, clearly the bigger chance we can achieve that score.
        - Now for a specific score, we need to find the proper root and the order of children nodes
        to see if we can traverse at least k nodes in the new graph (as we set alive[u] = 0 when a[i]
        < threshold and alive[u] = 1 otherwise, we don't eliminate nodes, just set an attribute for it)
        - So for a specific root, let's consider its children v, if we can fully traverse the subtree 
        root v, we can move to another subtree and continue to traverse (1). But if we cannot fully traverse
        one subtree, we have to stop there, so we choose the subtree with largest number of traversable
        nodes (2).
        - Let's define full[u] = number of nodes that we can fully traverse as (1), Max1[u] = number
        of nodes in (2), we define one more thing, Max2[u] = second largest number of nodes traversable 
        in another subtree distinct from (2)
        - So at each root u, res = max(res, (alive[u] ? full[u] + Max1[u].FI + 1 : 0)), clearly. When 
        we move down to make root as v, we have to update attributes of both u and v, remember to store
        the old values somewhere to return them to u and v later. One can check dfs3 to see what happens.
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

int n, k, a[MAXN], sum[MAXN], full[MAXN], res;
II Max1[MAXN], Max2[MAXN];
bool alive[MAXN];
vector<int> A[MAXN];

void dfs(int u, int p) {
    sum[u] = 1;
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (v == p) continue;
        dfs(v, u);
        sum[u] += sum[v];
    }
}

void dfs2(int u, int p) {
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (v == p) continue;
        dfs2(v, u);
        int x = (alive[v] ? full[v] + 1 : 0);
        if (x == sum[v]) full[u] += x;
        else {
            int MaxV = (alive[v] ? full[v] + Max1[v].FI + 1 : 0);
            if (MaxV > Max1[u].FI) Max1[u] = II(MaxV, v);
            else if (MaxV > Max2[u].FI) Max2[u] = II(MaxV, v);
        }
    }
}

void dfs3(int u, int p) {
    res = max(res, (alive[u] ? full[u] + Max1[u].FI + 1 : 0));
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (v == p) continue;

        // store values
        int oldFullU = full[u];
        II oldMax1U = Max1[u], oldMax2U = Max2[u];
        int oldFullV = full[v];
        II oldMax1V = Max1[v], oldMax2V = Max2[v];

        // update u
        int x = (alive[v] ? full[v] + 1 : 0);
        if (x == sum[v]) {
            // moving to one of the full
            full[u] -= x;
            // Max1, Max2 of u unchange
        } else if (v == Max1[u].SE) {
            // moving to Max1
            // full of u unchange
            Max1[u] = Max2[u];
            // no need to care about Max2 as we don't really need it to calculate the later values
            // we only need Max2 to replace Max1.
            // only lose Max2 when going down.
            Max2[u] = II(0, -1);
        } else {
            // nothing changes in u, clearly
        }

        // update full, Max of v
        int x2 = (alive[u] ? full[u] + 1 : 0);
        if (x2 == n - sum[v]) full[v] += x2;
        else {
            int MaxU = (alive[u] ? full[u] + Max1[u].FI + 1 : 0);
            if (MaxU > Max1[v].FI) Max1[v] = II(MaxU, u);
            else if (MaxU > Max2[v].FI) Max2[v] = II(MaxU, u);
        }

        dfs3(v, u);

        // refill u
        full[u] = oldFullU;
        Max1[u] = oldMax1U;
        Max2[u] = oldMax2U;

        // refill v
        full[v] = oldFullV;
        Max1[v] = oldMax1V;
        Max2[v] = oldMax2V;
    }
}

bool check(int threshold) {
    FOR(i,1,n) alive[i] = (a[i] >= threshold);
    FOR(i,1,n) {
        full[i] = 0;
        Max1[i] = Max2[i] = II(0, -1);
    }
    dfs2(1, 0);
    res = 0;
    dfs3(1, 0);
    return res >= k;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        A[u].push_back(v);
        A[v].push_back(u);
    }
    dfs(1, 0);
    int dau = 1, cuoi = 1000000;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (check(mid)) dau = mid+1;
        else cuoi = mid-1;
    }
    cout << cuoi;
    return 0;
}
