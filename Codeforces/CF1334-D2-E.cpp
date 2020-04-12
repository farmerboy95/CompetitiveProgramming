/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://codeforces.com/blog/entry/75877
        - Proof: https://codeforces.com/blog/entry/75877?#comment-601403
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

ll MOD = 998244353;

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

vector<ll> primes;
ll C[210][210];

vector<int> get(ll u) {
    vector<int> res;
    for (auto prime : primes) {
        int cnt = 0;
        while (u % prime == 0) {
            u /= prime;
            cnt++;
        }
        res.push_back(cnt);
    }
    return res;
}

ll calc(vector<int> &cnt, vector<int> &g) {
    FOR(i,0,SZ(cnt)-1) cnt[i] -= g[i];
    int sum = 0;
    FOR(i,0,SZ(cnt)-1) sum += cnt[i];

    // res = C(sum, cnt[0]) * C(sum-cnt[0], cnt[1]) * ...
    ll res = 1;
    FOR(i,0,SZ(cnt)-1) {
        res = mul(res, C[sum][cnt[i]]);
        sum -= cnt[i];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    ll D;
    cin >> D;
    ll d = D;
    // init C(n, k)
    FOR(i,0,200) FOR(j,0,i)
        if (j == 0 || j == i) C[i][j] = 1;
        else C[i][j] = add(C[i-1][j-1], C[i-1][j]);

    // get list of prime factors of D
    FOR(i,2,int(sqrt(D))) {
        if (d % i) continue;
        primes.push_back(i);
        while (d % i == 0) d /= i;
    }
    if (d > 1) primes.push_back(d);

    int q;
    cin >> q;
    while (q--) {
        ll u, v;
        cin >> u >> v;
        // get number of each prime factor in factorization of u and v
        vector<int> cnt1 = get(u);
        vector<int> cnt2 = get(v);
        // g = gcd of u, v
        vector<int> g(SZ(primes), 0);
        FOR(i,0,SZ(g)-1) g[i] = min(cnt1[i], cnt2[i]);
        // calculate result
        cout << mul(calc(cnt1, g), calc(cnt2, g)) << "\n";
    }
    return 0;
}
