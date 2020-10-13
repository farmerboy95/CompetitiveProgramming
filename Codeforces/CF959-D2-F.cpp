/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Problem 5: https://codeforces.com/blog/entry/68953
        - More explanation: https://codeforces.com/blog/entry/68953?#comment-655249

        (Rewrite the core idea here in case CF is down)
        - Assume you have l vectors and b of them form a basis B. Then all other l - b vectors
        can be represented as the xor of some basis vectors. Denote the set of all vectors that 
        can be represented as the xor of some basis vectors as "span B", notice that if x, y are
        in span B, then x xor y is also in span B.
        - Suppose we take a vector x in span B. Pick any subset of the "other l-b vectors", let 
        their XOR be K, then K is also in span B. If we wanted to pick some vectors such that 
        the XOR is x, and the XOR of the non-basis vectors we chose is K, then we need to pick 
        such basis vectors that their XOR is K xor x, and there is exactly one way to do that (because 
        B is a basis).
        - If we want to form x, we have 2^(l-b) ways to choose from the "non-basis vectors" and 
        1 way to choose from the basis vectors, so the answer is 2^(l-b).
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, q, a[MAXN], res[MAXN], mu[MAXN];
vector<II> query[MAXN];
int basis[20];
int D = 20, sz = 0;

void insertVector(int mask) {
    FOR(i,0,D-1) {
        if (!(mask & (1<<i))) continue;
        if (!basis[i]) {
            basis[i] = mask;
            sz++;
            return;
        }
        mask ^= basis[i];
    }
}

bool checkXor(int mask) {
    FOR(i,0,D-1) {
        if (!(mask & (1<<i))) continue;
        if (!basis[i]) return false;
        mask ^= basis[i];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    FOR(i,1,n) cin >> a[i];

    FOR(i,1,q) {
        int u, v;
        cin >> u >> v;
        query[u].push_back(II(v, i));
    }

    mu[0] = 1;
    FOR(i,1,n) mu[i] = mu[i-1] * 2 % MODBASE;

    FOR(i,1,n) {
        insertVector(a[i]);
        FOR(j,0,SZ(query[i])-1) {
            int v = query[i][j].FI;
            int pos = query[i][j].SE;
            if (checkXor(v)) res[pos] = mu[i - sz];
        }
    }

    FOR(i,1,q) cout << res[i] << "\n";
    return 0;
}
