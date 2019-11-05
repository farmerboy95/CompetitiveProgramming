/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: More or less like this submission https://github.com/stefdasca/CompetitiveProgramming/blob/master/COCI/COCI%2009-Palacinke.cpp
        - Formula dp[t][u] = dp[t-1][v] + dp[t-2][v] (if we have path from v to u)
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
const int MAXN = 200010;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;
const int MOD = 5557;

struct Edge {
    int u, v, mask;
    Edge(int u = 0, int v = 0, int mask = 0) : u(u), v(v), mask(mask) {}
};

int sub(int a, int b) {
    return (a - b + MOD) % MOD;
}

int add(int a, int b) {
    if (b >= 0) return (a+b) % MOD;
    return sub(a, -b);
}

int mul(int a, int b) {
    return a * b % MOD;
}

int toMask(string s) {
    int mask = 0;
    FOR(i,0,SZ(s)-1)
        if (s[i] == 'B') mask |= (1<<0);
        else if (s[i] == 'J') mask |= (1<<1);
        else if (s[i] == 'M') mask |= (1<<2);
        else mask |= (1<<3);
    return mask;
}

int n, m, t;
vector<Edge> e;

struct Matrix {
    int a[51][51];
    int n;
    Matrix(int n) {
        this->n = n;
        FOR(i,0,n-1) FOR(j,0,n-1) a[i][j] = 0;
    }
    Matrix operator * (Matrix &to) {
        Matrix ans(n);
        FOR(i,0,n-1)
            FOR(j,0,n-1)
                FOR(k,0,n-1) ans.a[i][j] = add(ans.a[i][j], mul(a[i][k], to.a[k][j]));
        return ans;
    }
};

int id(int u, int t) {
    return 1 + u*2 + t;
}

int solve(int mask) {
    Matrix A(2*n+1);
    Matrix B(2*n+1);
    FOR(i,0,2*n) B.a[i][i] = 1;
    // vector has form [number of paths so far, 1 (t), 1 (t-1), 2 (t), 2 (t-1),....]
    // set to get sum of number of paths from all nodes to 1
    A.a[0][0] = 1;
    // set to move paths from t-1 to t
    FOR(i,0,n-1) A.a[id(i, 1)][id(i, 0)] = 1;

    FOR(i,0,SZ(e)-1) {
        // path from t-1 to t
        A.a[id(e[i].v, 0)][id(e[i].u, 0)]++;
        // path from t-2 to t
        if (!(e[i].mask & mask)) A.a[id(e[i].v, 0)][id(e[i].u, 1)]++;

        // set to get number of paths from x to 1 at time t
        if (e[i].v == 0) {
            A.a[0][id(e[i].u, 0)]++;
            if (!(e[i].mask & mask)) A.a[0][id(e[i].u, 1)]++;
        }
    }

    int p = t;
    while (p) {
        if (p&1) B = B*A;
        A = A*A;
        p >>= 1;
    }
    // as init vector is [0, 1, 0, 0, 0 .....] => result = matrix[0][1];
    return B.a[0][id(0,0)];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        string s;
        cin >> u >> v >> s;
        u--;
        v--;
        e.emplace_back(Edge(u, v, toMask(s)));
    }
    cin >> t;
    int res = 0;
    FOR(mask,0,15) {
        int sign = 1;
        FOR(i,0,3)
            if (mask & (1<<i)) sign = -sign;
        res = add(res, sign * solve(mask));
    }
    cout << res;
    return 0;
}
