/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Sort the A[i], so every operation concerns a subsegment of indices. Let D[i] (1 <= i <= n+1) 
        be the xor between B[i] and B[i-1], where we consider that B[0] = B[n+1] = 0. Our objective is to 
        make D[] = 0. Notice that now every operation amounts to flipping the state of two elements of D.
        Let the range of the effect is L and R => Those 2 elements are L and R+1 (obviously)
        - Build a graph on 1..n+1 where indices i and j have an edge between them if an operation affects 
        both. Notice that if we have a simple cycle x_1, x_2, ..., x_k then flipping the edge from x_1 
        to x_k has the same effect as flipping the other k-1 edges, so it's enough to take a spanning 
        tree of each component. 
        - Now we can root each tree arbitrarily and greedily go from leaf to root, try to make all D[i]
        of a tree (except possibly the root) = 0. If at the end D[root] is still 1 => Impossible. 
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

int n, m, b[MAXN];
II a[MAXN];
vector<II> A[MAXN];
bool pick[MAXN], visit[MAXN];

int dfs(int u) {
    visit[u] = true;
    int x = b[u];
    FOR(i,0,SZ(A[u])-1) {
        int v = A[u][i].FI;
        int idx = A[u][i].SE;
        if (!visit[v] && dfs(v)) {
            x ^= 1;
            pick[idx] = true;
        }
    }
    return x;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i].FI >> a[i].SE;
    sort(a+1, a+n+1);
    FORE(i,n+1,1) b[i] = a[i].SE ^ a[i-1].SE;

    FOR(i,1,m) {
        int l, r;
        cin >> l >> r;
        int dau = 1, cuoi = n;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            if (a[mid].FI >= l) cuoi = mid-1;
            else dau = mid+1;
        }
        int L = dau;

        dau = 1, cuoi = n;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            if (a[mid].FI > r) cuoi = mid-1;
            else dau = mid+1;
        }
        int R = cuoi;
        if (L <= R && L >= 1 && L <= n+1 && R >= 1 && R <= n+1) {
            A[L].emplace_back(II(R+1, i));
            A[R+1].emplace_back(II(L, i));
        }
    }

    FOR(i,1,n)
        if (!visit[i] && dfs(i)) {
            cout << -1;
            return 0;
        }
    
    int res = 0;
    FOR(i,1,m) res += pick[i];
    cout << res << "\n";
    FOR(i,1,m) 
        if (pick[i]) cout << i << ' ';
    return 0;
}
