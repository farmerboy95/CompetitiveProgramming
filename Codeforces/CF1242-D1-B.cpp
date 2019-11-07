/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use set to save roots of connected components (CC)
        - Let's say we are considering u, it's in the CC of root U
        - Iterate all edges 1 starting from u, let's say one of them is (u, v), v is in the CC of root V
        - If U == V => u and v are in the same CC, ignore it
        - If U != V => they MAY BE in or NOT BE in the same CC
        - The condition for U to connect with V is that the number of edges starting from u to V is smaller than
        the number of nodes in the CC of root V (it can easily be seen that if it does not happen, there will be
        at least one edge connecting u and V)
        - So we move the CCs which do not connect with U to a new set, remove them from the current set and merge
        all CCs in the current set (it would need only n-1 times to merge in the whole program), move the new CC 
        to new set and use new set to consider next node u'.
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 5010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m, lab[MAXN], dem[MAXN];
vector<int> a[MAXN];
set<int> s, s2;

int getRoot(int u) {
    while (lab[u] > 0) u = lab[u];
    return u;
}
 
int unionFind(int u, int v) {
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[v] = u;
        lab[u] = x;
        return u;
    }
    else {
        lab[u] = v;
        lab[v] = x;
        return v;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }
    FOR(i,1,n) lab[i] = -1;

    FOR(i,1,n) s.insert(i);
    FOR(i,1,n) {
        s2.clear();
        int U = getRoot(i);

        // init dem, this array is for counting the number of edges from u to CC V
        FOR(j,0,SZ(a[i])-1) {
            int v = a[i][j];
            int V = getRoot(v);
            dem[V] = 0;
        }

        // start to count
        FOR(j,0,SZ(a[i])-1) {
            int v = a[i][j];
            int V = getRoot(v);
            if (U == V) continue;
            dem[V]++;
        }

        // compare
        FOR(j,0,SZ(a[i])-1) {
            int v = a[i][j];
            int V = getRoot(v);
            if (U == V) continue;
            if (dem[V] == -lab[V]) {
                s2.insert(V);
                s.erase(V);
            }
        }

        // merge all CCs in set s
        int first = 0;
        int now = 0;
        FORALL(it, s) {
            if (first == 0) {
                first = 1;
                now = *it;
            }
            else now = unionFind(now, *it);
        }
        // move the only CC from current set to new set
        s2.insert(now);
        s = s2;
    }
    cout << SZ(s) - 1;
    return 0;
}
