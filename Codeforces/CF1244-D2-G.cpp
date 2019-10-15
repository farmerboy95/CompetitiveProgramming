/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Example of minimum time for n = 5
        1 2 3 4 5
        1 2 3 4 5
        - Example of maximum time for n = 5
        1 2 3 4 5
        5 4 3 2 1
        => Min = n * (n+1) / 2
           Max = n * (n+1) / 2 
                + 2*m + (m-1)*m (n = 2*m+1 or n odd)
                + m + (m-1)*m   (n = 2*m or n even)
        - if k < Min => no result
        - otherwise, k = k - Min, let first array 1 2 3 ... n, then just put the largest number that fit k in to 1, 2 ... m
        sort the unused number and put into the remaining places.
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
const int MAXN = 1000010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, a[MAXN], b[MAXN];
ll k;
set<int> s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    if (k < (ll) n * (n+1) / 2) {
        cout << -1;
        return 0;
    }
    k -= (ll) n * (n+1) / 2;
    FOR(i,1,n) a[i] = i;
    FOR(i,1,n) s.insert(i);
    int m = n / 2;
    int last = 0;
    FOR(i,1,m) {
        int g = *s.rbegin();
        if (g - i > k) {
            int pick = -1;
            FORALL(it, s) {
                if (*it - i <= k) {
                    pick = max(pick, *it);
                }
            }
            s.erase(pick);
            b[i] = pick;
            last = i;
            break;
        }
        else {
            k -= g - i;
            s.erase(g);
            b[i] = g;
        }
    }
    if (last == 0) last = m;
    FORALL(it, s) {
        last++;
        b[last] = *it;
    }
    ll res = 0;
    FOR(i,1,n) res += max(a[i], b[i]);
    cout << res << "\n";
    FOR(i,1,n) cout << a[i] << ' ';
    cout << "\n";
    FOR(i,1,n) cout << b[i] << ' ';
    cout << "\n";
    return 0;
}
