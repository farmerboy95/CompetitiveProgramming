/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's take an example
                    A     abcdef
                    B   ababcd
        - Let ab[x] = false when all A[i] = B[j] (i - j = x), in the above example, x = -2, we consider
        spaces as character "?"
        - So x is the relative position of B to A, ab[x] = false means B can merge into A with relative
        position x
        - So we collect relative position of B to A, C to B and C to A, put them into array ab, bc, ac
        respectively.
        - Then we keep string A at position 0 and consider all pairs of relative position of B and C to
        A, then B and C also have their own relative position, if they are all false, we can get the 
        result.
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
const int MAXK = 100010;
const int MAXQ = 200010;

int M = 2000;
string a, b, c;
bool ab[MAXK], bc[MAXK], ac[MAXK];

bool match(char A, char B) {
    return (A == '?' || B == '?' || A == B);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> a >> b >> c;
    int A = SZ(a), B = SZ(b), C = SZ(c);

    FOR(i,0,A-1) FOR(j,0,B-1) if (!match(a[i], b[j])) ab[i-j+50000] = true;
    FOR(i,0,A-1) FOR(j,0,C-1) if (!match(a[i], c[j])) ac[i-j+50000] = true;
    FOR(i,0,B-1) FOR(j,0,C-1) if (!match(b[i], c[j])) bc[i-j+50000] = true;

    int res = 3*M;
    FOR(i,-2*M,2*M)
        FOR(j,-2*M,2*M)
            if (!ab[i+50000] && !ac[j+50000] && !bc[j-i+50000]) {
                int L = min(0, min(i, j));
                int R = max(A, max(B + i, C + j));
                res = min(res, R - L);
            }
    cout << res;
    return 0;
}
