/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Requirement 1: We do not need to care about edges that belong to at least 2 triangles. Take out
        edges belonging to 1 triangle and do the dfs to print out the result.
        - Requirement 2: Edges that belong to at least 2 triangles connect triangles together. As we have
        n-2 triangles and n-3 cuts, this will form a tree. Recreate that tree and dfs the tree, cut from leaves
        to root.
*/
 
#include "bits/stdc++.h"
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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;
 
int t, n, a[MAXN][3];
vector<int> A[MAXN], B[MAXN];
bool visited[MAXN];
map<II, vector<int> > ma;
 
void dfs(int u, int p) {
    cout << u << ' ';
    visited[u] = true;
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i];
        if (v == p) continue;
        if (!visited[v]) dfs(v, u);
    }
}
 
void dfs2(int u, int p) {
    FOR(i,0,SZ(B[u])-1) {
        int v = B[u][i];
        if (v == p) continue;
        dfs2(v, u);
    }
    cout << u << ' ';
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        FOR(i,1,n-2) {
            cin >> a[i][0] >> a[i][1] >> a[i][2];
            sort(a[i], a[i]+3);
        }
        FOR(i,1,n) {
            A[i].clear();
            B[i].clear();
            visited[i] = false;
        }
        ma.clear();
        FOR(i,1,n-2) {
            ma[II(a[i][0], a[i][1])].emplace_back(i);
            ma[II(a[i][0], a[i][2])].emplace_back(i);
            ma[II(a[i][1], a[i][2])].emplace_back(i);
        }
 
        FORALL(it, ma) {
            if (SZ(it->SE) == 2) {
                int u = it->SE[0], v = it->SE[1];
                B[u].emplace_back(v);
                B[v].emplace_back(u);
            }
            else {
                int u = it->FI.FI, v = it->FI.SE;
                A[u].emplace_back(v);
                A[v].emplace_back(u);
            }
        }
 
        FOR(i,1,n-2) {
            if (SZ(ma[II(a[i][0], a[i][1])]) == 1) {
                A[a[i][0]].emplace_back(a[i][1]);
                A[a[i][1]].emplace_back(a[i][0]);
            }
            if (SZ(ma[II(a[i][0], a[i][2])]) == 1) {
                A[a[i][0]].emplace_back(a[i][2]);
                A[a[i][2]].emplace_back(a[i][0]);
            }
            if (SZ(ma[II(a[i][1], a[i][2])]) == 1) {
                A[a[i][1]].emplace_back(a[i][2]);
                A[a[i][2]].emplace_back(a[i][1]);
            }
        }
 
        dfs(1, 0);
        cout << "\n";
        FOR(i,1,n-2)
            if (SZ(B[i]) <= 1) {
                dfs2(i, 0);
                cout << "\n";
                break;
            }
    }
    return 0;
}