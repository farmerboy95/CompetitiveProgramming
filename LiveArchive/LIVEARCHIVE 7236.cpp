/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First we create tree T1 and T2 based on input strings. It's quite easy to do.
        - We define some arrays in the implementation:
            + ch1[u], ch2[u]: Character at node u of tree T1, T2, respectively.
            + sum1[u], sum2[u]: Number of nodes of subtree of u of tree T1, T2, respectively.
            + pre1[u], pre2[u]: Each node v has a number of child nodes u in some order, pre1[u] = the node that is
            iterated right before node u, the same thing applied to pre2[u].
            + prefSum1[u], prefSum2[u]: Sum of number of nodes of subtrees from the first iterated node to node u.
        - Let dp[u][U] = tree edit distance of subtree u of T1 and subtree U of T2. Then we have to match immediate children
        of u and that of U so that the tree edit distance is minimal. One observation here is that it's quite the same
        as the original edit distance problem, we use dp2[v][V] for this. There are 3 cases here:
            + Add a subtree of V in T2: dp2[v][V] = dp2[v][pre2[V]] + sum2[V]
            + Delete a subtree of v in T1: dp2[v][V] = dp2[pre1[v]][V] + sum1[V]
            + Transform subtree of v to subtree of V: dp2[v][V] = dp2[pre1[v]][pre2[V]] + dp[v][V] 
        - The above transitions are simplified, one should consider cases where there is no pre1[v] or pre2[V] to add
        or remove a number of subtrees
        - What's the complexity here? For each node u, let the number of children of u = c(u). So for each state (u, U)
        we need to do O(c(u) * c(U)) operations.
        => O(sum(c(u)) * sum(c(U))) = O(n * m) (easy to see)
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
const int MAXN = 1010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int R[50010], numNode, pre1[MAXN], pre2[MAXN], sum1[MAXN], sum2[MAXN], prefSum1[MAXN], prefSum2[MAXN];
int dp[MAXN][MAXN], dp2[MAXN][MAXN];
char ch1[MAXN], ch2[MAXN];
vector<int> a[2][MAXN];

int createNode(string &s, int l, int r, char *ch, int idx) {
    numNode++;
    ch[numNode] = s[l+1];
    l += 2;
    r -= 1;
    int u = numNode;
    for (int i = l; i <= r; ) {
        int v = createNode(s, i, R[i], ch, idx);
        a[idx][u].push_back(v);
        i = R[i] + 1;
    }
    return u;
}

int createTree(string &s, char *ch, int idx) {
    FOR(i,1,1000) a[idx][i].clear();
    stack<int> st;
    int n = SZ(s);
    FOR(i,0,n-1)
        if (s[i] == '(') st.push(i);
        else if (s[i] == ')') {
            int l = st.top();
            st.pop();
            R[l] = i;
        }
    numNode = 0;
    return createNode(s, 0, n-1, ch, idx);
}

int handle(int u, int U) {
    if (dp[u][U] != -1) return dp[u][U];
    int &res = dp[u][U];
    res = 0;
    int add = (ch1[u] != ch2[U]);
    int n = SZ(a[0][u]), m = SZ(a[1][U]);
    if (n == 0 && m == 0) res = add;
    else if (n == 0) res = add + prefSum2[a[1][U][m-1]];
    else if (m == 0) res = add + prefSum1[a[0][u][n-1]];
    else {
        FOR(i,0,n-1)
            FOR(j,0,m-1) {
                int v = a[0][u][i], V = a[1][U][j];
                dp2[v][V] = 1e9;

                if (pre2[V] == -1) dp2[v][V] = min(dp2[v][V], sum2[V] + prefSum1[v]);
                else dp2[v][V] = min(dp2[v][V], sum2[V] + dp2[v][pre2[V]]);

                if (pre1[v] == -1) dp2[v][V] = min(dp2[v][V], sum1[v] + prefSum2[V]);
                else dp2[v][V] = min(dp2[v][V], sum1[v] + dp2[pre1[v]][V]);


                int x = handle(v, V);
                if (pre1[v] == -1 && pre2[V] == -1) dp2[v][V] = min(dp2[v][V], x);
                else if (pre1[v] == -1) dp2[v][V] = min(dp2[v][V], x + prefSum2[pre2[V]]);
                else if (pre2[V] == -1) dp2[v][V] = min(dp2[v][V], x + prefSum1[pre1[v]]);
                else dp2[v][V] = min(dp2[v][V], x + dp2[pre1[v]][pre2[V]]);
            }
        res = add + dp2[a[0][u][n-1]][a[1][U][m-1]];
    }
    return res;
}

void dfs(int u, int idx, int *sum, int *prefSum, int *pre) {
    sum[u] = 1;
    FOR(i,0,SZ(a[idx][u])-1) {
        int v = a[idx][u][i];
        if (i == 0) pre[v] = -1;
        else pre[v] = a[idx][u][i-1];
        dfs(v, idx, sum, prefSum, pre);
        sum[u] += sum[v];
    }
    FOR(i,0,SZ(a[idx][u])-1) {
        int v = a[idx][u][i];
        if (i == 0) prefSum[v] = sum[v];
        prefSum[v] = prefSum[pre[v]] + sum[v];
    }
}

int solve(string &s, string &t) {
    int root1 = createTree(s, ch1, 0);
    int root2 = createTree(t, ch2, 1);
    dfs(root1, 0, sum1, prefSum1, pre1);
    dfs(root2, 1, sum2, prefSum2, pre2);
    MS(dp, -1);
    return handle(root1, root2);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        string s, t;
        cin >> s >> t;
        cout << solve(s, t) << "\n";
    }
    return 0;
}
