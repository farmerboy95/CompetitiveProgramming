/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First, number of permutations of a sequence of length n = n! / (b! * c! * d! * ...) 
        b, c, d... are number of occurences of distinct elements of the sequence
        - Example: 1 2 2 2 4 4 9 10 10 10
        => number of permutations = 10! / (1! * 3! * 2! * 1! * 3!)

        - Turn back to our problem, we need to count the number of permutations that are smaller than
        our initial sequence. More specifically, for each a[i] from 1 to n, we need to count the number 
        of permutations that have smaller element at i than a[i] (1), add it to the result. After each i, 
        we fix a[i] at i and continue to count.

        - For each a[i], we count number of smaller element than a[i] in the sequence (coeff), we can easily prove
        that (1) = coeff * (n - i)! / (b! * c! * d! * ...). As we increase i, (1) = (1) / (n-i) * b (assume that a[i] 
        occurs b times in the sequence)
        - coeff can be calculated by using BIT (Fenwick Tree)
        
        - The obstacle here is the modulo m, which can be prime or composite, a ^ phi(m) = 1 (mod m) 
        is correct iff a and m are coprimes, so we need to extract prime factors of m in a and calculate 
        separately
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
typedef pair<ll, ll> II;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 300010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], t[MAXN], cnt[MAXN], b[MAXN], pos[MAXN], phi;
ll bare[MAXN], inv[MAXN], m;
vector<int> primeList, cntPrime;

void update(int u, int val) {
    while (u <= n) {
        t[u] += val;
        u = u + (u & (-u));
    }
}

int get(int u) {
    int res = 0;
    while (u) {
        res += t[u];
        u = u - (u & (-u));
    }
    return res;
}

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

void updateCntPrime(int p, int val) {
    // update occurence of each prime in prime factor list of m (max 9 primes)
    FOR(j,0,SZ(primeList)-1)
        while (p % primeList[j] == 0) {
            p /= primeList[j];
            cntPrime[j] += val;
        }
}

ll getCntPrimeProd() {
    // get (prime[0] ^ count[0] * prime[1] ^ count[1] * ...) % m
    ll res = 1;
    FOR(j,0,SZ(primeList)-1) res = res * binPowMod(primeList[j], cntPrime[j], m) % m;
    return res;
}

void reindex() {
    FOR(i,1,n) b[i] = a[i];
    sort(b+1, b+n+1);
    int idx = 0;
    FOR(i,1,n)
        if (b[i] != b[i-1]) {
            idx++;
            pos[b[i]] = idx;
        }
    FOR(i,1,n) a[i] = pos[a[i]];
}

void calcBareInv(int k) {
    int p = k;
    FOR(j,0,SZ(primeList)-1)
        while (p % primeList[j] == 0) p /= primeList[j];
    // bare[k] is k after removing prime factors of m
    bare[k] = p % m;
    // inv[k] is modulo inverse of bare[k]
    inv[k] = binPowMod(bare[k], phi-1, m);
}

// not calculating bare and inv again using memorization
ll getBare(int k) {
    if (bare[k] != 0) return bare[k];
    calcBareInv(k);
    return bare[k];
}

ll getInv(int k) {
    if (bare[k] != 0) return inv[k];
    calcBareInv(k);
    return inv[k];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];

    // reindex a[i] to reduce BIT limit as time limits for first several tests are tight
    reindex();

    // get all prime factors of m and calculate phi(m)
    int M = int(m);
    phi = M;
    FOR(i,2,int(sqrt(m)))
        if (M % i == 0) {
            primeList.emplace_back(i);
            cntPrime.emplace_back(0);
            phi -= phi / i;
            while (M % i == 0) M /= i;
        }
    if (M > 1) {
        primeList.emplace_back(M);
        cntPrime.emplace_back(0);
        phi -= phi / M;
    }

    // init BIT
    FOR(i,1,n) {
        update(a[i], 1);
        cnt[a[i]]++;
    }

    // init x = n! / (a! * b! * c! * ....)
    ll mainPart = 1;
    FOR(i,1,n)
        if (cnt[i] > 1)
            FOR(j,2,cnt[i]) {
                mainPart = mainPart * getInv(j) % m;
                updateCntPrime(j, -1);
            }
    FOR(i,2,n) {
        mainPart = mainPart * getBare(i) % m;
        updateCntPrime(i, 1);
    }

    int now = n;
    ll res = 1;
    FOR(i,1,n) {
        int coeff = get(a[i]-1);

        // x = x / n
        mainPart = mainPart * getInv(now) % m;
        updateCntPrime(now, -1);

        if (coeff) {
            // x = x * coeff
            mainPart = mainPart * getBare(coeff) % m;
            updateCntPrime(coeff, 1);

            res = (res + mainPart * getCntPrimeProd() % m) % m;

            // x = x / coeff
            // because coeff is not going with us to the next i
            mainPart = mainPart * getInv(coeff) % m;
            updateCntPrime(coeff, -1);
        }

        // x = x * b
        mainPart = mainPart * getBare(cnt[a[i]]) % m;
        updateCntPrime(cnt[a[i]], 1);

        // remove 1 a[i]
        cnt[a[i]]--;
        update(a[i], -1);

        now--;
    }
    cout << res;
    return 0;
}