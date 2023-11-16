/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First simplify: X = x_1^x_2...^x_N^x_1'^x_2'^...^x_N'
        - Now all pairs (x_i, y_i) become (0, x_i^y_i)
        - So after A's moves then you have some value of X. What does B do to minimize? B should 
        try to remove max bit of X if possible. What if B can do this with more than one number?
        - We replace B's numbers with basis of B's numbers. So if most significant bits of B's 
        basis are b_1 > b_2 > ... > b_k then x will have none of these bits after the reduction.
        - We then replace A's numbers with basis of A's numbers. We can't just find the max # 
        that A can make. For each number in A's basis, reduce by basis of B -> no number will 
        have any of the bits b_1,b_2,...,b_k
        - So now, we're done because we can just find max XOR in modification of A's basis.
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
const int MAXN = 20010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;
ll x[MAXN], y[MAXN];
const int D = 60;
ll basis[D], basis2[D], basis3[D];

void insertVector(ll *basis, ll mask) {
    FORE(i,D-1,0) {
        if (!(mask & (1LL<<i))) continue;
        if (!basis[i]) {
            basis[i] = mask;
            return;
        }
        mask ^= basis[i];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        FOR(i,1,n+m) cin >> x[i] >> y[i];
        MS(basis, 0);
        MS(basis2, 0);
        MS(basis3, 0);
        ll origin = 0;
        FOR(i,1,n+m) origin ^= x[i];
        FOR(i,1,n) insertVector(basis, x[i] ^ y[i]);
        FOR(i,n+1,n+m) insertVector(basis2, x[i] ^ y[i]);
        // minimum number that you can create, the result will be larger or equal to this origin
        FORE(i,D-1,0)
            if (origin & (1LL << i))
                if (basis2[i]) origin ^= basis2[i];
        
        FORE(i,D-1,0)
            if (basis[i]) {
                ll x = basis[i];
                // For each number in A's basis, reduce by basis of B -> no number will have any of the bits b_1,b_2,...,b_k
                FORE(j,D-1,0)
                    if (x & (1LL << j))
                        if (basis2[j]) x ^= basis2[j];
                insertVector(basis3, x);
            }
        
        // find max
        FORE(i,D-1,0)
            if (!(origin & (1LL << i)))
                if (basis3[i]) origin ^= basis3[i];

        cout << origin << "\n";
    }
    return 0;
}