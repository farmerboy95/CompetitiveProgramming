/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://atcoder.jp/contests/arc105/editorial/202
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

int t, n;
unordered_map<int, int> ma;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        ma.clear();
        FOR(i,1,n) {
            int x;
            cin >> x;
            ma[x]++;
        }
        if (n % 2 == 0) {
            bool co = true;
            FORALL(it, ma)
                if (it->SE % 2) co = false;
            if (co) cout << "Second\n";
            else cout << "First\n";
        } else cout << "Second\n";
    }
    return 0;
}
