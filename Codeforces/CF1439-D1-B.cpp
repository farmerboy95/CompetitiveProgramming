/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - In the first case, our clique will have k * (k-1) / 2 edges. In the second case, our set
        will have at least k * (k + 1) / 2 edges. So if number of edges < k * (k-1) / 2, there is no
        solution. Notice that k now would be around 500.
        - Now assume that we currently use the whole graph. We first try to find the set.
        - There would be some nodes with less than k neighbors, those nodes of course cannot be
        included in our set, so we remove them (using set or heap to manage number of neighbors).
        In the end, there are 2 cases: the heap still has some nodes => we have the result, otherwise,
        we move on to find the clique (as it requires less number of neighbors than the set case).
        - We do the same thing to find the clique. If in the end, there is not enough nodes to get the
        clique, simply print -1.
        - Here is the interesting part. Each time we pop one node out of the heap, the number of
        neighbors of it would be exactly k-1. Why? Because if it's larger than k-1, the set case
        will have the answer, but in fact not. Now we have the current node and its neighbors. We
        can simply check if they can form a clique in O(k^2). If not, we remove it. 
        - One more observation is that, each time we remove a node, we also remove k-1 edges. So
        there would be m / (k-1) clique candidates. The overall complexity would be O(k^3). May have
        some log(n) for the heap.
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

int n, m, k, t;
unordered_set<int> a[MAXN];
set<II> b;
vector<II> edges;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        FOR(i,1,n) {
            a[i].clear();
            edges.clear();
        }
        FOR(i,1,m) {
            int u, v;
            cin >> u >> v;
            edges.push_back(II(u, v));
            a[u].insert(v);
            a[v].insert(u);
        }
        if ((ll) k * (k-1) / 2 > m) {
            cout << -1 << "\n";
            continue;
        }

        // try to find the set (case 2)
        b.clear();
        FOR(i,1,n)
            if (SZ(a[i])) b.insert(II(SZ(a[i]), i));
        
        while (SZ(b)) {
            II g = *b.begin();
            if (g.FI >= k) break;
            int u = g.SE;
            b.erase(b.begin());
            FORALL(it, a[u]) {
                int v = *it;
                b.erase(II(SZ(a[v]), v));
                a[v].erase(u);
                b.insert(II(SZ(a[v]), v));
            }
        }
        // if possible, print it out
        if (SZ(b)) {
            cout << 1 << ' ' << SZ(b) << "\n";
            FORALL(it, b) cout << it->SE << ' ';
            cout << "\n";
            continue;
        }

        // re-init edges and do the same thing to find the clique.
        FOR(i,1,n) a[i].clear();
        FOR(i,1,m) {
            int u = edges[i-1].FI, v = edges[i-1].SE;
            a[u].insert(v);
            a[v].insert(u);
        }
        b.clear();
        FOR(i,1,n)
            if (SZ(a[i])) b.insert(II(SZ(a[i]), i));
        
        while (SZ(b)) {
            II g = *b.begin();
            if (g.FI >= k-1) break;
            int u = g.SE;
            b.erase(b.begin());
            FORALL(it, a[u]) {
                int v = *it;
                b.erase(II(SZ(a[v]), v));
                a[v].erase(u);
                b.insert(II(SZ(a[v]), v));
            }
        }

        // if there is not enough nodes to get a clique, print -1
        if (SZ(b) < k) {
            cout << -1 << "\n";
            continue;
        }

        vector<int> res;
        while (SZ(b)) {
            II g = *b.begin();
            int u = g.SE;
            if (g.FI == k-1) {
                vector<int> p;
                p.push_back(u);
                FORALL(it, a[u]) {
                    int v = *it;
                    p.push_back(v);
                }
                bool co = true;
                FOR(i,0,SZ(p)-1)
                    FOR(j,i+1,SZ(p)-1) {
                        int U = p[i], V = p[j];
                        if (!a[U].count(V)) {
                            co = false;
                            break;
                        }
                    }
                if (co) {
                    res = p;
                    break;
                }
            }

            b.erase(b.begin());
            FORALL(it, a[u]) {
                int v = *it;
                b.erase(II(SZ(a[v]), v));
                a[v].erase(u);
                b.insert(II(SZ(a[v]), v));
            }
        }
        if (SZ(res)) {
            cout << 2 << "\n";
            for (int x : res) cout << x << ' ';
            cout << "\n";
            continue;
        }

        cout << -1 << "\n";
    }
    return 0;
}
