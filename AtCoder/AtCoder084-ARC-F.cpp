/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://img.atcoder.jp/arc084/editorial.pdf
        - You can perform the following operations for the polynomials:
            + Multiply a polynomial by x. (corresponds to ”double") (F(x) -> xF(x))
            + Compute the sum of two polynomials. (corresponds to ”xor”) 
        - After getting GCD, then you can use above 2 operations properly to get all multiples
        of G (H = H'G). How to get this? As multiplication by x increase the power of each term
        by one (a.k.a. left bitwise shift). So, to multiply polynomials f(x) * g(x) we can multiply 
        f(x) by each term of g(x) separately, each being equivalent to a shift, and then add, the 
        addition being equivalent to XOR (https://stackoverflow.com/questions/13202758/multiplying-two-polynomials).
        - So we need to compute the number of polynomial P such that P is a multiple of G and
        P is less than or equal to X (as a binary number).
        - We have the GCD = G, we can use the first operation to create a vector space, which
        contain numbers G, G<<1, G<<2, G<<3,.... Let the most significant bit of G is at index d.
        From the basis, we can create any number with set / unset bit i >= d, and for each of those
        numbers, the last d-1 bits are uniquely determined.
        - So if a bit at index i of X is set, and i >= d, we can set it in our result to 0 and
        it's now surely smaller than X, res += 2^(i-d). Now we have to set it to 1, which means
        we have to XOR our result by the basis at i, which is G << (i-d).
        - After proceeding all the bit indices >= d, as the last d-1 bits are uniquely determined,
        we have to check if the number now is smaller or equal (res++) or not.
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
const int MAXN = 10;
const int MAXM = 4010;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
string x;
ll mu[MAXM];
ll MOD = 998244353;
bitset<4000> X, G;

// O(4000^2)
bitset<4000> gcd(bitset<4000> A, bitset<4000> B) {
    int i;
    // make A > B first
    for (i = 3999; i >= 0; i--)
        if (A[i] == 1 && B[i] == 1) {
            B ^= A;
            break;
        }
        else if (A[i] == 1) break;
        else if (B[i] == 1) {
            swap(A, B);
            break;
        }
    // now A > B
    while (1) {
        int j;
        for (j = i-1; j >= 0; j--)
            if (B[j]) break;
        if (j < 0) break;
        // raise the most significant bit of B to that of A and xor until A < B
        while (i >= j) {
            if (A[i]) A^= B << (i-j);
            i--;
        }
        i = j;
        // swap and do again until we find GCD
        swap(A, B);
    }
    return A;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    // O(N*4000^2) if not using bitset
    // O(N*4000^2/m) if using bitset, m = 32 or 64

    mu[0] = 1;
    FOR(i,1,4000) mu[i] = mu[i-1] * 2 % MOD;

    cin >> n >> x;
    FOR(i,0,SZ(x)-1)
        if (x[i] == '1') X[SZ(x)-1-i] = 1;

    FOR(i,1,n) {
        cin >> x;
        bitset<4000> Y;
        FOR(j,0,SZ(x)-1)
            if (x[j] == '1') Y[SZ(x)-1-j] = 1;
        if (i == 1) G = Y;
        else G = gcd(G, Y);
    }
    ll res = 0;

    // x = the most significant bit of G
    int x = 0;
    FOR(i,0,3999)
        if (G[i]) x = i;
    
    bitset<4000> Y;
    FORE(i,3999,x) {
        if (X[i]) res += mu[i-x];
        if (X[i]^Y[i]) Y ^= (G << (i-x));
    }

    // check our Y to see if Y <= X, if yes => res++
    res++;
    FORE(i,x-1,0)
        if (Y[i] < X[i]) break;
        else if (X[i] < Y[i]) {
            res--;
            break;
        }

    cout << res % MOD;
    return 0;
}
