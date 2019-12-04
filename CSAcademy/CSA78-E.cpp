/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Same idea as infoarena xortransform
        - https://github.com/farmerboy95/CompetitiveProgramming/blob/master/infoarena/infoarena%20xortransform.cpp
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
const int MAXN = 210;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct SplitMix64 {
    unsigned long long nextInt() {
        unsigned long long z = (x += 0x9E3779B97F4A7C15ULL);
        z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
        z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
        return z ^ (z >> 31);
    }
    
    int random() {
        return 1 + (nextInt() >> 33);
    }
    
    unsigned long long x;
};

int n, m, q, dp[9000000], Max = 1;
SplitMix64 rng;

int query(int x) {
    x &= Max-1;
    return dp[x];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> q >> rng.x;
    FOR(i,0,n-1)
        FOR(j,0,m-1) {
            int x = rng.random();
            dp[i|j] ^= x;
        }

    while (Max < n || Max < m) Max <<= 1;

    FOR(i,0,22)
        FOR(mask,0,(1<<23)-1)
            if (mask & (1<<i)) dp[mask] ^= dp[mask ^ (1<<i)];

    unsigned long long hashSol = 0;
    FOR(i,1,q) hashSol ^= (unsigned long long)i * query(rng.random());

    cout << hashSol;
    return 0;
}
