/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use the technique here to find the basis vectors with f(vecB) is the last position
        with a set bit: https://codeforces.com/blog/entry/68953
        - Now we iterate from dimension D-1 to 0. At first, let's say the number of basis vectors
        is sz, so we have 2^sz different values to be created. So if basis[i] is not 0, means there
        is a basis vector at dimension i, there are 2 ways, add it to xor sum or not to add it to
        xor sum. If we choose to add it to xor sum, there would definitely be 2^(sz-1) values that 
        are smaller than the current xor sum (as we cannot change the ith bit later). That's the key
        of the problem. If k <= 2^(sz-1), we don't add basis[i] to xor sum, otherwise, we add it
        to xor sum. It would take us O(D) to find the Kth smallest xor sum.
        - Note that except the first basis[i] > 0 from D-1 to 0, later j which has basis[j] > 0 may
        encounter the case that bit jth of the current result is set. In that case, we simply reverse
        the process, add to come to smaller values, not to add to come to bigger values.
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

const int D = 30;
int basis[D], s[D], mu[D];

void insertVector(int mask) {
    FORE(i,D-1,0) {
        if (!(mask & (1<<i))) continue;
        if (!basis[i]) {
            basis[i] = mask;
            return;
        }
        mask ^= basis[i];
    }
}

int getKthSmallest(int k) {
    s[0] = (basis[0] != 0);
    FOR(i,1,D-1) s[i] = s[i-1] + (basis[i] != 0);
    int now = 0;
    FORE(i,D-1,0)
        if (basis[i]) {
            int smaller = 1;
            if (i - 1 >= 0) smaller = mu[s[i-1]];
            if (now & (1<<i)) {
                if (k > smaller) k -= smaller;
                else now = now ^ basis[i];
            } else {
                if (k > smaller) {
                    now = now ^ basis[i];
                    k -= smaller;
                }
            }
        }
    return now;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, u, v;
    cin >> n;
    mu[0] = 1;
    FOR(i,1,D-1) mu[i] = mu[i-1] * 2;
    while (n--) {
        cin >> u >> v;
        if (u == 1) {
            insertVector(v);
        } else {
            cout << getKthSmallest(v) << "\n";
        }
    }
    return 0;
}
