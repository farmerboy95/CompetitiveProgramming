/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Put all strings into a trie tree, save initial position of a string at the end of each
        string in trie (node->pos), also need to mark if a string is included in set S (node->isRes)
        - Let's start with a node that is not in set S, we can easily see that this node can only be 
        reached by its parent, i.e. res[v->pos] = res[u->pos] + 1 (node u is parent of node v)
        - What about nodes that are in set S? Let's consider one such node, this node can also be
        reached by its parent (obviously) but it can also be reached by all of its ancestors, let's
        consider one ancestor x, so res[v->pos] = min(res[x->pos] + number of nodes that are in set S
        in the dfs order from x to v, order should be lexicographical + 1)
        - So how can we solve the second case? We may call cnt as number of nodes that are in set S
        from a specific node u, then use dfs to count number of such nodes in order of dfs. We also
        need to store "Min", which is minimum of (res[x->pos] + number of nodes that are in set S
        in the dfs order from x to v, order should be lexicographical), then recursively calculate
        new Min as we face a marked node. See the code for more info.
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
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct TrieNode {
    TrieNode *children[26];
    bool isRes;
    int pos;
}; 

TrieNode *getNode() {
    TrieNode *pNode =  new TrieNode;
    pNode->isRes = false;
    pNode->pos = -1;
    FOR(i,0,25) pNode->children[i] = nullptr; 
    return pNode; 
}

TrieNode* a[MAXN];
int n, b[MAXN], res[MAXN];

int dfs(TrieNode* u, int Min) {
    if (u->isRes) res[u->pos] = min(res[u->pos], Min+1);
    int cnt = u->isRes;
    FOR(i,0,25) {
        if (!u->children[i]) continue;
        int v = u->children[i]->pos;
        res[v] = res[u->pos] + 1;
        cnt += dfs(u->children[i], min(Min, res[u->pos]) + cnt);
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    a[0] = getNode();
    a[0]->pos = 0;
    FOR(i,1,n) {
        int u; char ch;
        cin >> u >> ch;
        a[i] = getNode();
        a[i]->pos = i;
        a[u]->children[ch - 'a'] = a[i];
    }
    int m;
    cin >> m;
    FOR(i,1,m) {
        cin >> b[i];
        a[b[i]]->isRes = true;
    }

    res[0] = 0;
    dfs(a[0], 0);

    FOR(i,1,m) cout << res[b[i]] << ' ';
    return 0;
}
