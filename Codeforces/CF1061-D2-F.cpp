/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - More or less like https://codeforces.com/blog/entry/63384
        - More comments in code
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
const int MAXN = 1510;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, k, h, l1, l2, a[MAXN];
vector<int> b, path;

bool query(int a, int b, int c) {
    cout << "? " << a << ' ' << b << ' ' << c << endl;
    string s;
    cin >> s;
    return s[0] == 'Y';
}

void print(int u) {
    cout << "! " << u << endl;
    exit(0);
}

int getLeaf() {
    // find one leaf
    while (1) {
        shuffle(a+1, a+n+1, rng);
        // check if the chosen node is between any pair of nodes
        // if not => it's the leaf
        int leaf = a[1], random = a[2];
        bool co = true;
        FOR(i,3,n) {
            co &= (query(random, leaf, a[i]) == 0);
            if (!co) break;
        }
        if (co) return leaf;
    }
}

int getLeaf2() {
    // find a leaf in other subtree of the actual root
    while (1) {
        shuffle(a+1, a+n+1, rng);
        // chosen node must not be the same as leaf 1
        if (a[1] == l1) continue;
        // number of nodes between leaf 1 and leaf 2 is 2 * (h-1) - 1
        // if the chosen node satisfies the above condition => it's the leaf we need
        int cnt = 0, leaf = a[1];
        // need to store the nodes between leaf1 and leaf2 for the next step
        b.clear();
        FOR(i,2,n) {
            if(a[i] == l1) continue;
            bool x = query(l1, a[i], leaf);
            cnt += x;
            if (x) b.push_back(a[i]);
        }
        if (cnt == 2 * (h-1) - 1) return leaf;
    }
}

void findRoot() {
    // one node in the array b must be between 2 consecutive nodes in path
    path.push_back(l1);
    path.push_back(b[0]);
    path.push_back(l2);
    FOR(i,1,SZ(b)-1) {
        vector<int> newPath;
        newPath.push_back(path[0]);
        FOR(j,1,SZ(path)-1) {
            // if b[i] is between path[j-1] and path[j]
            // add b[i] to newPath and add the rest of path to newPath
            if (query(path[j-1], b[i], path[j])) {
                newPath.push_back(b[i]);
                FOR(k,j,SZ(path)-1) newPath.push_back(path[k]);
                break;
            } else newPath.push_back(path[j]);
        }
        // move newPath to path
        path = newPath;
    }
    // print the middle one, path[h-1], as one leaf is path[0]
    print(path[h-1]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    // corner case
    if (n == 1) print(1);

    // h = height of the tree
    // height of tree with 1 node = 1
    h = 1;
    int num = 1, cur = k;
    while (num + cur <= n) {
        num += cur;
        cur *= k;
        h++;
    }

    // array a for shuffle
    FOR(i,1,n) a[i] = i;
    l1 = getLeaf();
    l2 = getLeaf2();
    findRoot();

    return 0;
}
