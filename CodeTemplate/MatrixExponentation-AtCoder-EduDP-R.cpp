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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
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

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 55;
const int MAXM = 1000010;
const int MAXK = 100010;
const int MAXQ = 200010;

int n, a[MAXN][MAXN];
ll k;
  
ll sub(ll x, ll y) {
    return (x-y+MODBASE) % MODBASE;
}

ll add(ll x, ll y) {
    return (x+y)%MODBASE;
}

ll mul(ll x, ll y) {
    return ((x%MODBASE) * (y%MODBASE)) % MODBASE;
}

struct Matrix {
    vector<vector<ll> > a;
    int n;
    Matrix(int n) {
        this->n = n;
        a.clear();
        vector<ll> b(n, 0);
        FOR(i,0,n-1) a.emplace_back(b);
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
    cin >> n >> k;
    FOR(i,0,n-1) FOR(j,0,n-1) cin >> a[i][j];
    Matrix ONE(n);
    FOR(i,0,n-1) ONE.a[i][i] = 1;
    Matrix now(n);
    FOR(i,0,n-1)
        FOR(j,0,n-1) now.a[i][j] = a[j][i];
    Matrix res = mu(now, k, ONE);
    vector<ll> fi(n, 1);
    fi = res * fi;
    ll kq = 0;
    FOR(i,0,n-1) kq = (kq + fi[i]) % MODBASE;
    cout << kq;
    return 0;
}
