/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Idea from https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2016/contest3_solutions/solutions.pdf
        - More or less like https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2016/contest3_solutions/nekameleoni.cpp
        - We define a balance binary tree, each node manages a specific range of init array.
        - As we have K <= 50, for each node, we define pref[50] and suff[50] that store pair(bitmask of 
        found numbers and the smallest pos from the left / the furthest pos from the right that we achieve
        that bitmask)
        - When we update a node, we update from the leaf to the root of the tree and update parent of 
        a changed node by merging left child and right child of that parent.
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 50;
const int MAXNODES = 262144;
const int offset = 131072;

int n, m, k;

struct Node {
    int len;
    II pref[50], suff[50];
    int res;

    Node() { 
        res = 1000000000; 
        len = 0;
    }

    // creating one node
    Node(int t, int v) {
        len = 1;
        pref[0] = suff[0] = II(1LL<<v, t);
        res = 1000000000;
    }
};

Node tree[MAXNODES];

// a is subset of b
bool isSubset(ll a, ll b) {
    return (a & b) == a;
}

void merge(Node &a, Node &l, Node &r) {
    int prefLen = 0, suffLen = 0;
    // first, we copy left part of a and right part of b, putting them to a.pref and a.suff
    FOR(i,0,l.len-1) a.pref[prefLen++] = l.pref[i];
    // then after handling all the left part of a, we try to seek if there are new states
    // by concatenating r.pref to a.pref
    FOR(i,0,r.len-1)
        if (prefLen == 0 || !isSubset(r.pref[i].FI, a.pref[prefLen-1].FI)) {
            a.pref[prefLen] = r.pref[i];
            if (prefLen) a.pref[prefLen].FI |= a.pref[prefLen-1].FI;
            prefLen++;
        }

    // do the same thing to suffix
    FOR(i,0,r.len-1) a.suff[suffLen++] = r.suff[i];
    FOR(i,0,l.len-1)
        if (suffLen == 0 || !isSubset(l.suff[i].FI, a.suff[suffLen-1].FI)) {
            a.suff[suffLen] = l.suff[i];
            if (suffLen) a.suff[suffLen].FI |= a.suff[suffLen-1].FI;
            suffLen++;
        }
    
    // prefLen and suffLen should be equal
    a.len = prefLen;
    a.res = 1000000000;

    // this part should be conducted in O(k) using 2 pointers
    // let suffPos is the left most part of l, then we move prefPos to the right from 0 to r.len
    // and update the result if we find a pair of bitmasks that cover all k numbers.
    int prefPos = 0;
    FORE(suffPos,l.len-1,0) {
        while (prefPos < r.len && (l.suff[suffPos].FI | r.pref[prefPos].FI) != (1LL<<k)-1) prefPos++;
        if (prefPos < r.len) {
            ll currMask = l.suff[suffPos].FI | r.pref[prefPos].FI;
            if (currMask == (1LL<<k)-1) a.res = min(a.res, r.pref[prefPos].SE-l.suff[suffPos].SE+1);
        }
    }

    // re-update the result
    a.res = min(a.res, min(l.res, r.res));
}

void update(int u, int x) {
    // first layer has one node (root), second layer has 2 nodes, third layer has 4 nodes
    // and so on, so to make the last layer contains at least 10^5 nodes, it would be the
    // 18th layer (2^17 nodes), so in total we have 2^18-1 nodes
    // we start from the last layer and go up, merging childs of parents
    u += offset;
    tree[u] = Node(u - offset, x);
    for (u /= 2; u; u /= 2) merge(tree[u], tree[2*u], tree[2*u+1]);
}

int getRes() {
    if (tree[1].res == 1000000000) return -1;
    return tree[1].res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k >> m;
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        x--;
        update(i, x);
    }
    while (m--) {
        int ch;
        cin >> ch;
        if (ch == 2) {
            cout << getRes() << "\n";
        }
        else {
            int u, x;
            cin >> u >> x;
            update(u-1, x-1);
        }
    }
    return 0;
}
