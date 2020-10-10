/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as: https://discuss.codechef.com/t/xorcmpnt-editorial/25928
        - The "vector space basis" technique (or bitwise gaussian elmination): https://codeforces.com/blog/entry/68953
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

int t, k, m, basis[50], sz;

void insertVector(int mask) {
    FOR(i,0,k-1) {
        if (!(mask & (1<<i))) continue;
        if (!basis[i]) {
            basis[i] = mask;
            sz++;
            return;
        }
        mask ^= basis[i];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> k >> m;
        MS(basis, 0);
        sz = 0;
        FOR(i,1,m) {
            int x;
            cin >> x;
            insertVector(x);
        }
        cout << (1<<(k - sz)) << endl;
    }
    return 0;
}
