/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2011/round-2/problems/B
    Status: AC
    Idea:
        - Mainly from https://aholzner.wordpress.com/2011/02/07/facebook-hacker-cup-round-2-problem-1-some-discussion/
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
const int MAXN = 250010;
const int MAXM = 1000;
const int MAXP = 250010;
const int MAXQ = 200010;
const ld PI = acos(-1);

int P, L;
int N, M;
ll a[MAXN], b[MAXN];
vcd A, B, fa, fb, fh, H;
ll A1, A2, A3, A4, A5, B1, B2, B3, B4, B5;

void input() {
    cin >> P >> L;
    cin >> N >> A1 >> A2 >> A3 >> A4 >> A5;
    cin >> M >> B1 >> B2 >> B3 >> B4 >> B5;
}

void buildA() {
    FOR(i,0,P-1) a[i] = 0;
    // a[x] = number of x in the first sequence
    a[A1]++;
    a[A2]++;
    FOR(i,3,N) {
        ll x = (A1 * A3 + A2 * A4 + A5) % P;
        a[x]++;
        A1 = A2;
        A2 = x;
    }
}

void buildB() {
    FOR(i,0,P-1) b[i] = 0;
    // b[x] = number of x in the second sequence
    b[B1]++;
    b[B2]++;
    FOR(i,3,M) {
        ll x = (B1 * B3 + B2 * B4 + B5) % P;
        b[x]++;
        B1 = B2;
        B2 = x;
    }
}

int getPhi(int n) {
    int res = n;
    FOR(i,2,int(sqrt(n)))
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    if (n > 1) res -= res / n;
    return res;
}

ll binPowMod(ll a, ll b, ll MOD) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1LL;
    }
    return res;
}

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int primitiveRootGenerator(int p) {
    if (p <= 1) return -1;
    if (p == 2) return 1;
    int phi = getPhi(p), n = phi;
    // get prime factors of phi(n)
    vector<int> fact;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0) n /= i;
        }
    if (n > 1) fact.push_back(n);

    FOR(res,2,p) {
        if (gcd(res, p) > 1) continue;
        bool ok = true;
        for (int x : fact) ok &= (binPowMod(res, phi / x, p) != 1);
        if (ok) return res;
    }
    return -1;
}

// only for sz(a) == 2^x
vcd fft(const vcd &a) {
    int n = SZ(a);
    int k = 0;
    while ((1<<k) < n) k++;
    vector<int> rev(n);

    // 10110 -> rev = 01101
    rev[0] = 0;
    int high1 = -1;
    FOR(i,1,n-1) {
        if ((i & (i-1)) == 0) high1++;
        rev[i] = rev[i ^ (1<<high1)];
        rev[i] |= (1 << (k-high1-1));
    }

    // roots of unity w(n) ^ k = cos(2pi * k / n) + i * sin(2pi * k / n)
    vcd roots(n);
    FOR(i,0,n-1) {
        ld alpha = 2 * PI * i / n;
        roots[i] = cd(cos(alpha), sin(alpha));
    }

    vcd cur(n);
    FOR(i,0,n-1) cur[i] = a[rev[i]];

    // going from leaves to the root of the tree (deepest depth to the root)
    for (int len = 1; len < n; len <<= 1) {
        // next depth
        vcd ncur(n);

        // rstep = radian step
        // so for length len, we need len roots of unity, w(len * 2) ^ k, 0 <= k <= len-1
        // in other words, we consider w on one half of the circle
        int rstep = SZ(roots) / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            FOR(i,0,len-1) {
                cd val = roots[i * rstep] * cur[p1 + len];
                ncur[pdest] = cur[p1] + val;
                ncur[pdest + len] = cur[p1] - val;
                pdest++; p1++;
            }
            pdest += len;
        }

        // move next depth to current depth
        cur.swap(ncur);
    }

    return cur;
}

// only for sz(a) == 2^x
vcd fftRev(const vcd &a) {
    vcd res = fft(a);
    FOR(i,0,SZ(res)-1) res[i] /= SZ(a);
    reverse(res.begin()+1, res.end());
    return res;
}

ll solve() {
    buildA();
    buildB();

    // corner case
    ll res = 0;
    FOR(i,0,P-1) res += a[0] * b[i];
    FOR(i,1,P-1) res += b[0] * a[i];

    // no need to care about a[0], b[0] anymore
    // write each x[i] as x[i] = g ^ y[i], where y[i] is called the discrete logarithm of x[i] 
    // with respect to the basis g, g must be a primitive root modulo P to ensure that for any 
    // integer x[i] in [1, P-1], there is a value y[i] which satisfies this equation.
    int g = primitiveRootGenerator(P);
    ll now = 1;
    // resize and fill polynomial A and B
    A.resize(2 * (P-1));
    B.resize(2 * (P-1));
    fill(ALL(A), 0);
    fill(ALL(B), 0);
    // now = g^i, so here we reorder the array a and b to A and B respectively
    // for example, a[x] is number of x in the first sequence, but x = g^y as described above
    // we transform array a to polynomial A to make the result be the multiplication of 2
    // polynomials.
    FOR(i,0,P-2) {
        A[i] = a[now];
        B[i] = b[now];
        now = now * g % P;
    }

    int k = 0;
    while ((1<<k) < SZ(A)) k++;
    while (SZ(A) < (1<<k)) A.push_back(0);

    k = 0;
    while ((1<<k) < SZ(B)) k++;
    while (SZ(B) < (1<<k)) B.push_back(0);

    fa = fft(A);
    fb = fft(B);

    fh.resize(SZ(fa));

    FOR(i,0,SZ(A)-1) fh[i] = fa[i] * fb[i];
    H = fftRev(fh);

    now = 1;
    FOR(i,0,SZ(H)-1) {
        ll val = (ll) (H[i].real() + 0.5);
        // val = number of pairs with product equals to g^i mod P
        if (now < L) res += val;
        now = now * g % P;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        input();
        cout << "Case #" << o << ": " << solve() << "\n";
    }
    return 0;
}
