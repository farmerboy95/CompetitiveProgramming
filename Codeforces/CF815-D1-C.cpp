/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Reconstruct the tree using dp sibling technique
        - Let dp[u][K][p] is the minimum amount of money that we need to buy K goods in the subtree 
        of u, p = 0 means we cannot use coupon at u, otherwise p = 1
        - Remember to add limit L, R (use only possible range) in general case to make the complexity O(N^2)
        - Proof: Initially you have the size of 1. When you get a subtree of size S you'll make a 
        S * size transition and then you'll make size += S. On the first step, you'll pair the 
        current vertex with all the vertices from the subtree. From the second step onwards, you'll 
        pair the current vertex AND the already counted vertices with the vertices of the next subtree 
        (the number of such pair is S * size). This means that you'll never count any pair twice and 
        the complexity will be exactly the number of such pairs, or O(n^2)
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
const int MAXN = 5010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, b, num2[MAXN], leftChild[MAXN], sibling[MAXN];
int dp[MAXN][MAXN][2];
int cost[MAXN], discount[MAXN];
vector<int> a[MAXN];

// reconstruct the tree
void dfs(int u) {
    int pre = -1;
    for (int v : a[u]) {
        if (pre == -1) leftChild[u] = v;
        else sibling[pre] = v;
        pre = v;
        dfs(v);
    }
}

void dfs2(int u) {
    num2[u] = 1;
    if (leftChild[u] != -1) {
        dfs2(leftChild[u]);
        num2[u] += num2[leftChild[u]];
    }
    if (sibling[u] != -1) {
        dfs2(sibling[u]);
        num2[u] += num2[sibling[u]];
    }
}

// isRoot = 1 means that node u is in the root component
int solve(int u, int K, int isRoot) {
    if (dp[u][K][isRoot] != -1) return dp[u][K][isRoot];

    int &res = dp[u][K][isRoot];
    if (K == 0) return res = 0;
    if (num2[u] < K) return res = 1000000001;
    int l = leftChild[u], s = sibling[u], val = (isRoot ? discount[u] : cost[u]);

    // u is leaf and has no sibling, K must be 1
    if (l == -1 && s == -1) {
        res = val;
    }

    // u has child but has no sibling
    if (l != -1 && s == -1) {
        res = min(solve(l, K, 0), solve(l, K-1, isRoot) + val);
    }

    // u is leaf and has sibling
    if (l == -1 && s != -1) {
        res = min(solve(s, K, isRoot), solve(s, K-1, isRoot) + val);
    }

    // general case
    if (l != -1 && s != -1) {
        res = 1000000001;
        if (num2[s] >= K) res = min(res, solve(s, K, isRoot));
        // get the possible range of number of nodes which can be distributed to child and sibling
        int L = max(1, K-num2[s]), R = min(K, num2[l]+1);
        FOR(i,L,R) res = min(res, solve(s, K-i, isRoot) + min(solve(l, i-1, isRoot) + val, solve(l, i, 0)));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> b;
    FOR(i,1,n) leftChild[i] = sibling[i] = -1;
    cin >> cost[1] >> discount[1];
    // cost[i] = amount of money needed without coupon
    // discount[i] = amount of money needed with coupon
    cost[1] -= discount[1];
    discount[1] = cost[1];
    FOR(i,2,n) {
        int par;
        cin >> cost[i] >> discount[i] >> par;
        discount[i] = cost[i] - discount[i];
        a[par].emplace_back(i);
    }
    dfs(1);
    dfs2(1);
    MS(dp, -1);
    // iteration or binary search here are the same
    int dau = 1, cuoi = n;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (solve(1, mid, 1) <= b) dau = mid+1;
        else cuoi = mid-1;
    }
    cout << cuoi;
    return 0;
}
