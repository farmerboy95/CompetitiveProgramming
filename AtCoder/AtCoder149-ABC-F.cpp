/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - As nodes are independent, we can calculate expected number of nodes which are inside S in each node.
        In other words, for each node u, we calculate res[u] = the probability that node u is inside S.
        => Result = sum(res[u])
        - Each node u has a number of edges x connecting it with some other nodes. 
        - If x = 1, there is no way that u is inside S.
        - Otherwise, u is inside S iff there are at least 2 components that contain black nodes if we disconnect
        u from the tree.
        => res[u] = 1/2 * (1 - (prob 0 component) - (prob 1 component)) (since the probability of having white node u is 1/2)
        - Note that the probability of having at least 1 black nodes in a component of size sz = 1 - (1/2) ^ sz
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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll binPowMod(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

ll inv(ll u) {
    return binPowMod(u, MODBASE-2, MODBASE);
}

ll add(ll a, ll b) {
    return (a + b) % MODBASE;
}

ll mul(ll a, ll b) {
    return a * b % MODBASE;
}

ll sub(ll a, ll b) {
    return (a - b + MODBASE) % MODBASE;
}

int n, s[MAXN];
ll res[MAXN], allWhite[MAXN];
vector<int> a[MAXN];

void dfs(int u, int p) {
    s[u] = 1;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (v == p) continue;
        dfs(v, u);
        s[u] += s[v];
    }
    if (SZ(a[u]) == 1) return;
    ll inv2 = inv(2);
    res[u] = inv2;
    ll prod = inv2;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        int sz = (v == p) ? (n - s[u]) : s[v];
        allWhite[v] = binPowMod(inv2, sz, MODBASE);
        prod = mul(prod, allWhite[v]);
    }
    res[u] = sub(res[u], prod);
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        ll e = mul(prod, inv(allWhite[v]));
        e = mul(e, sub(1, allWhite[v])); // have black
        res[u] = sub(res[u], e);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n-1) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(v);
        a[v].emplace_back(u);
    }
    dfs(1, 0);
    ll kq = 0;
    FOR(i,1,n) kq = add(kq, res[i]);
    cout << kq;
    return 0;
}
