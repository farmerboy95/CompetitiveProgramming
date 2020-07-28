/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2020/qualification-round/problems/B
    Status: AC
    Idea:
        - We first observe that it's like removing 2 different consecutive elements from the array.
        - It means that at each step, we remove one A and one B, so the number of As and Bs must be
        different by 1 for us to make n / 2 operations.
        - Is that enough to find the result? Yes, let's suppose that we have an array that |numA - numB| = 1
        So at any step, we can always find 1 pair (A, B) or (B, A) next to each other. We simply don't care
        about the third element because we just need to remove the pair away, and |numA - numB| = 1 after
        the operation. If n = 1, it's clearly YES. So the above induction proves the result.
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

int t, n;
string s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n;
        cin >> s;
        int cnt = 0;
        FOR(i,0,n-1) cnt += s[i] == 'A';
        cout << (abs(cnt - (n - cnt)) == 1 ? "Y" : "N") << "\n";
    }
    return 0;
}
