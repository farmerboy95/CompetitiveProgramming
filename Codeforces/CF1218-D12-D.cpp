/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let sumXor = xor sum of all edges
        - We have at most 42 simple cycle. Choose one edge each cycle to minimize the xor sum of
        them and sumXor.
        - We describe each cycle as the frequency polynomial and use Fast Walsh-Hadamard Transform
        (FWHT) to do the polynomial multiplication with modulo
        - Then choose the i with minimum xor sum with sumXor and there is at least one way to form
        it and print the result.
        - But wait, what if the result divisible by 10^9+7? We do another multiplication chain
        using another prime modulo and check both of them to know if there is at least one way to
        form a xor sum.
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

int n, m, visited[MAXN], low[MAXN], num[MAXN], dfsNum;
stack<III> s;
vector<II> a[MAXN];
vector<vector<int> > group;

ll MOD = MODBASE;
ll MOD2 = 77886769;

ll binPowMod(ll a, ll b, ll mod) {
    a %= mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % mod;
        a = a * a % mod;
        b >>= 1LL;
    }
    return res;
}

void dfs(int u, int p) {
    num[u] = low[u] = ++dfsNum;
    visited[u] = 1;
    for (II x : a[u]) {
        int v = x.FI, c = x.SE;
        if (v == p) continue;
        if (num[v] == 0) {
            s.push(III(II(u, v), c));
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= num[u]) {
                III r;
                vector<int> g;
                do {
                    r = s.top();
                    s.pop();
                    g.push_back(r.SE);
                } while (r.FI != II(u, v) && r.FI != II(v, u));
                if (SZ(g) > 1) group.push_back(g);
            }
        }
        else {
            // back edge
            if (num[v] < num[u]) s.push(III(II(u, v), c));
            low[u] = min(low[u], num[v]);
        }
    }
}

void FWHT(vector<int> &P, bool inverse, ll mod, int revN) {
    int n = SZ(P);
    for (int len = 1; 2 * len <= n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            FOR(j,0,len-1) {
                int u = P[i + j];
                int v = P[i + len + j];
                P[i + j] = (u + v) % mod;
                P[i + len + j] = (u - v + mod) % mod;
            }
        }
    }
    
    if (inverse)
        FOR(i,0,n-1) P[i] = (ll) P[i] * revN % mod;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    int sumXor = 0;
    FOR(i,1,m) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u].push_back(II(v, c));
        a[v].push_back(II(u, c));
        sumXor ^= c;
    }
    dfs(1, 0);

    int N = (1<<17);
    int revN = binPowMod(N, MOD-2, MOD);
    int revN2 = binPowMod(N, MOD2-2, MOD2);

    vector<int> res(N), res2(N);
    res[0] = 1;
    res2[0] = 1;
    FWHT(res, 0, MOD, revN);
    FWHT(res2, 0, MOD2, revN2);

    FOR(i,0,SZ(group)-1) {
        vector<int> b(N, 0);
        FOR(j,0,SZ(group[i])-1) b[group[i][j]]++;
        FWHT(b, 0, MOD, revN);
        FOR(j,0,N-1) res[j] = (ll) res[j] * b[j] % MOD;

        vector<int> c(N, 0);
        FOR(j,0,SZ(group[i])-1) c[group[i][j]]++;
        FWHT(c, 0, MOD2, revN2);
        FOR(j,0,N-1) res2[j] = (ll) res2[j] * c[j] % MOD2;
    }

    FWHT(res, 1, MOD, revN);
    FWHT(res2, 1, MOD2, revN2);

    int Min = 1000000, cnt = 0;
    FOR(i,0,N-1) {
        if (res[i] == 0 && res2[i] == 0) continue;
        if ((sumXor ^ i) < Min) {
            Min = sumXor ^ i;
            cnt = res[i];
        }
    }
    cout << Min << ' ' << cnt;
    return 0;
}
