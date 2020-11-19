/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's take a look at our operation, there are 2 possibilities:
            + 11 -> 00
            + 01 -> 10
        - So we can remove 2 consecutive 1s, or we can move 1 from i to i-1.
        - As the number of 1s can only be decreased (by 2), number of 1s of S should be larger
        than that of T, moreover, the parity of those should be the same.
        - As we can only move 1 to the left (or to delete 11), we can proceed the array from left
        to right. If the numbers at the current position of 2 arrays are not equal, we have to look
        for the nearest 1 to the right of the position of S. Note that we only look for 1 in array S
        and we are sure that from the current position to the nearest 1, the numbers in S are all 0,
        so we can just keep looking forward.
        - Note that result should be long long int
        - Complexity O(N)
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

int n;
string s, t;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    cin >> s >> t;
    s = " " + s;
    t = " " + t;
    int numS = 0, numT = 0;
    FOR(i,1,n) numS += (s[i] == '1');
    FOR(i,1,n) numT += (t[i] == '1');
    if (numS < numT) {
        cout << -1;
        return 0;
    }
    if (numS % 2 != numT % 2) {
        cout << -1;
        return 0;
    }
    int i = 1, j = 1;
    ll res = 0;
    while (j <= n) {
        if (s[j] == t[j]) {
            j++;
        } else if (s[j] == '0' && t[j] == '1') {
            bool co = false;
            FOR(u,i+1,n)
                if (s[u] == '1') {
                    res += u - j;
                    swap(s[j], s[u]);
                    i = u;
                    co = true;
                    break;
                }
            if (!co) {
                cout << -1;
                return 0;
            }
            j++;
        } else {
            bool co = false;
            FOR(u,i+1,n)
                if (s[u] == '1') {
                    res += u - j;
                    s[j] = s[u] = '0';
                    i = u;
                    co = true;
                    break;
                }
            if (!co) {
                cout << -1;
                return 0;
            }
            j++;
        }
        i = max(i, j);
    }
    cout << res;
    return 0;
}
