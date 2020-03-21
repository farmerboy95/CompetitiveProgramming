/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Result = a^n * x - (a^n + a^(n-1) + ... + a)
        - We can use matrix multiplication to solve the expression in bracket
        - DO NOT USE modular inverse because c may divide a-1
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll MOD;

ll binPowMod(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

struct Matrix {
    vector<vector<ll> > a;
    int n;
    Matrix(int N) {
        this->n = N;
        a.clear();
        vector<ll> b(N, 0);
        FOR(i,0,N-1) a.emplace_back(b);
    }
    Matrix operator * (Matrix &to) {
        Matrix ans(n);
        FOR(i,0,n-1)
            FOR(j,0,n-1)
                FOR(k,0,n-1) ans.a[i][j] = add(ans.a[i][j], mul(a[i][k], to.a[k][j]));
        return ans;
    }
    vector<ll> operator * (vector<ll> to) { 
        vector<ll> ans(n);
        FOR(i,0,n-1)
            FOR(j,0,n-1) ans[i] = add(ans[i], mul(a[i][j], to[j]));
        return ans;
    }
};

Matrix mu(Matrix A, ll n, Matrix B) {
    while (n) {
        if (n&1) B = B*A;
        A = A*A;
        n >>= 1;
    }
    return B;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    ll x, a, n, c;
    while (cin >> x >> a >> n >> c && !(x == 0 && n == 0 && a == 0 && c == 0)) {
        MOD = c;
        ll res = mul(binPowMod(a, n), x);

        Matrix ONE(2);
        FOR(i,0,1) ONE.a[i][i] = 1;
        Matrix now(2);
        now.a[0][0] = now.a[0][1] = a;
        now.a[1][1] = 1;
        Matrix m = mu(now, n, ONE);
        vector<ll> fi(2, 0);
        fi[1] = 1;
        fi = m * fi;
        cout << sub(res, fi[0]) << "\n";
    }
    return 0;
}
