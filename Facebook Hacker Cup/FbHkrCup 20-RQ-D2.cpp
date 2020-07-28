/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2020/qualification-round/problems/D2
    Status: AC
    Idea:
        - Let's form a road from A to B. Take A as root and dfs. Then from B, we go to parent
        until reaching A and form a road from A to B. Let's call the road b[1] ... b[k].
        - There are some observations needed to solve this problem:
            1. If we move to b[i], we don't need to go back to b[j] to refill (j < i).
            2. From b[1] (A), we don't need to go to the subtree that does not contain B to refill.
            3. After reaching b[k] (B), we don't need to go anywhere else.
            4. Each b[i] (i = 2...k-1) will have its own subtree (only the root on the direct path),
            the nodes which are not on the direct path might also be used. We don't need to go to 
            node j which is a distance of M away or more from node b[i] to refill (because it would
            take us another refill in the subtree).
            5. When reaching a node j in a subtree to refill, we don't need to go to another node
            in the same subtree to refill (because it's better to go to that node in the first place)
        - So it's optimal to go to the subtree to refill (not including the root) once and go out right
        away.
        - We basically do as the same as D1, maintain a min heap. But when going to the subtree,
        we use BFS to traverse. If we want to remove something from the heap, remember to place the
        removed one somewhere and add the ones that you will add to the heap somewhere else. We would
        put all of them into the heap after we fully traverse the subtree. Distance between nodes can
        be calculated by: distance(node1, root1) + distance(root1, root2) + distance(node2, root2).
        - Complexity O(NlogN)
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
typedef pair<ll, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, st, en, par[MAXN], c[MAXN], pos[MAXN];
ll dp[MAXN];
II d[MAXN];
vector<int> a[MAXN], A[MAXN], b;
priority_queue<II, vector<II>, greater<II> > h;
vector<II> tmpDel, willAdd;

void init() {
    FOR(i,1,n) {
        a[i].clear();
        A[i].clear();
        dp[i] = 0;
    }
    b.clear();
    while (!h.empty()) h.pop();
}

void dfs(int u, int p) {
    for (int v : a[u]) {
        if (v == p) continue;
        par[v] = u;
        dfs(v, u);
    }
}

void dfs2(int u, int p) { 
    d[u] = II(d[p].FI + 1, d[p].SE);
    for (int v : a[u]) {
        if (v == p) continue;
        A[u].push_back(v);
        dfs2(v, u);
    }
}

int getLen(int u, int v) {
    return abs(pos[u] - pos[v]);
}

int getDist(int u, int v) {
    int root1 = d[u].SE;
    int dist1 = d[u].FI;
    int root2 = d[v].SE;
    int dist2 = d[v].FI;
    return getLen(root1, root2) + dist1 + dist2;
}

void input() {
    cin >> n >> m >> st >> en;
    init();
    FOR(i,1,n) {
        cin >> par[i] >> c[i];
        if (par[i]) {
            a[par[i]].push_back(i);
            a[i].push_back(par[i]);
        }
    }
}

void iterateChild(int root) {
    tmpDel.clear();
    willAdd.clear();

    queue<int> q;
    q.push(root);
    while (SZ(q)) {
        int u = q.front(); q.pop();
        for (int v : A[u]) {
            if (d[v].FI >= m) break;
            ll picked = -1;
            while (SZ(h)) {
                II r = h.top();
                if (getDist(r.SE, v) > m) {
                    tmpDel.push_back(r);
                    h.pop();
                    continue;
                }
                picked = r.FI;
                break;
            }
            dp[v] = picked;
            if (picked != -1 && c[v]) willAdd.push_back(II(picked + c[v], v));
            q.push(v);
        }
    }

    for (II x : tmpDel) h.push(x);
    for (II x : willAdd) h.push(x);
}

ll solve() {
    input();
    dfs(st, 0);

    int now = en;
    b.push_back(now);
    while (now != st) {
        now = par[now];
        b.push_back(now);
    }
    reverse(ALL(b));

    FOR(i,0,SZ(b)-1) pos[b[i]] = i;
    d[b[0]] = II(0, b[0]);
    d[b[SZ(b)-1]] = II(0, b[SZ(b)-1]);

    FOR(i,1,SZ(b)-2) {
        int u = b[i];
        d[u] = II(0, u);
        for (int v : a[u]) {
            if (v == b[i-1] || v == b[i+1]) continue;
            A[u].push_back(v);
            dfs2(v, u);
        }
    }

    h.push(II(0, b[0]));
    dp[b[0]] = 0;

    FOR(i,1,SZ(b)-1) {
        int u = b[i];
        ll picked = -1;
        while (SZ(h)) {
            II r = h.top();
            if (getDist(r.SE, u) > m) {
                h.pop();
                continue;
            }
            picked = r.FI;
            break;
        }
        dp[u] = picked;
        if (picked != -1 && c[u]) h.push(II(picked + c[u], u));
        iterateChild(u);
    }

    return dp[en];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) cout << "Case #" << o << ": " << solve() << "\n";
    return 0;
}
