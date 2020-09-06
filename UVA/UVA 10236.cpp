/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://github.com/sggutier/CompetitiveProgramming/blob/master/UVa/10236.cpp
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
using ld = long double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 250010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

bool nt[MAXN];
vector<ll> res;

// https://www.geeksforgeeks.org/given-number-n-find-first-k-digits-nn/
ll calc(ld product) {
    // remove the integer part
    ld decimal_part = product - floorl(product);
    // raise the decimal part with base 10
    decimal_part = powl(10, decimal_part);
    // retrieve first 9 digits of it
    ll digits = powl(10, 9 - 1);
    return decimal_part * digits;
}

void init() {
    // use something like Eratosthene's sieve to filter Fibo primes
    FOR(i,3,250000)
        if (!nt[i]) 
            for (int j = 2 * i; j <= 250000; j += i) nt[j] = true;
    // nth fibo number is close to phi^n / sqrt(5) => log10 = n * log10(phi) - log10(sqrt(5))
    ld phi = (1 + sqrtl(5)) / 2;
    ld lp = log10l(phi);
    ld lr = log10l(sqrt(5));
    // calculate cases when fibo number < 10^9
    // other cases, use the above fact
    ll a = 1, b = 1, c = 0;
    FOR(i,3,250000) {
        if (c < 1e9) c = a + b;
        if (nt[i]) {
            if (c < 1e9) {
                a = b;
                b = c;
            }
            continue;
        }
        if (c >= 1e9) res.push_back(calc(i * lp - lr));
        else {
            a = b;
            b = c;
            res.push_back(c);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    init();
    int x;
    while (cin >> x) cout << res[x-1] << "\n";
    return 0;
}
