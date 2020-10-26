/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Store the position of "+" into a stack with number x, with x indicates that the numbers
        in the stack should be larger than x. The one which was placed earlier in the stack has
        stronger constraint.
        - Now we can do it like a bracket sequence, + is (, - is ). If the number u <= x of the top
        of the stack, we can say the answer is NO. Otherwise, we update the new x into the new top
        of the stack.
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

int res[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int cnt = 0;
    vector<II> s;
    FOR(i,1,2*n) {
        char ch; int u;
        cin >> ch;
        if (ch == '-') {
            cin >> u;
            if (SZ(s) == 0) {
                cout << "NO";
                return 0;
            }
            II r = s.back(); s.pop_back();
            int pos = r.FI, Min = r.SE;
            if (u <= Min) {
                cout << "NO";
                return 0;
            }
            res[pos] = u;
            if (SZ(s)) s.back().SE = max({s.back().SE, u, Min});
        } else {
            cnt++;
            s.push_back(II(cnt, 0));
        }
    }
    cout << "YES\n";
    FOR(i,1,n) cout << res[i] << ' ';
    return 0;
}
