/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Sort all C[i] in increasing order.
        - For example, if we choose some of N C[i] and start to do operation, we
        definitely have to do operation from the smallest C[i] to the largest to get
        the minimum cost.
        - So, consider a specific i, how many times C[i] will be added to the final result?
        - Let's consider a number of times C[i] * j (1 <= j <= N-i+1) is added to the result,
        it would be 2 * C(n-i, j-1) * 2^(n-i) * 4^(i-1)
            + 2: At i, there are 2 cases that the numbers at i are different (1/0, 0/1)
            + C(n-i, j-1): C[i] * j => we need j-1 positions to the right of i
            + 2^(n-i): After choosing j-1 positions in n-i positions to the right of i, we
            also have 2^(n-i) ways to form the first sequence from i+1 to n, the number of
            second sequence corresponded to each first sequence is 1 (clearly).
            + 4^(i-1): How about the right part? As it does not affect value of j, we can
            choose whatever S and T, which is 4^(i-1) ways.
        - So at each i, number that we need to add to the result is 
        sum(C(n-i, j-1) * j) * 2^(n-i+1) * 4^(i-1) * C[i]
        - Wait, how to calculate sum(C(n-i, j-1) * j) (1 <= j <= n-i+1) quickly? 
        - Or generally, how to calculate sum(C(n, k) * (k+1)) quickly?
        - Well, sum(C(n, k) * (k+1)) = sum(C(n, k) * k + C(n, k)) = sum(C(n, k) * k) + sum(C(n, k))
        = (n * 2^(n-1)) + 2^n
        Proof: (x+1)^n = sum(C(n,k) * x^k)
               then by taking derivative, n * (x+1)^(n-1) = sum(k * C(n,k) * x^(k-1))
               Let x = 1 => n * 2^(n-1) = sum(k * (C(n, k)))
        => sum(C(n-i, j-1) * j) = (n-i) * 2^(n-i-1) + 2^(n-i)
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

ll binPowMod(ll a, ll b) {
    a %= MODBASE;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MODBASE;
        a = a * a % MODBASE;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a+b) % MODBASE;
}

ll mul(ll a, ll b) {
    return (a*b) % MODBASE;
}

ll sub(ll a, ll b) {
    return (a-b+MODBASE) % MODBASE;
}

ll f[MAXN], inv[MAXN], c[MAXN];
int n;

ll C(int N, int K) {
    if (K > N || K < 0) return 0;
    return mul(f[N], mul(inv[N-K], inv[K]));
}

void init() {
    f[0] = 1;
    inv[0] = binPowMod(f[0], MODBASE-2);
    FOR(i,1,200000) {
        f[i] = mul(f[i-1], i);
        inv[i] = binPowMod(f[i], MODBASE-2);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    init();
    
    cin >> n;
    
    FOR(i,1,n) cin >> c[i];
    sort(c+1, c+n+1);
    ll res = 0;
    FOR(i,1,n) {
        ll sum = add(binPowMod(2, n-i) ,mul(n-i, binPowMod(2, n-i-1)));
        res = add(res, mul(mul(binPowMod(2, n-i+1), binPowMod(4, i-1)), mul(c[i], sum)));
    }
    cout << res;
    return 0;
}
