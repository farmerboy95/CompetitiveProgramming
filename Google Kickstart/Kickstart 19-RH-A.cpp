/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 
        - Let the initial H-index = 0
        - After reading each number x, we check how many numbers in the array is larger than H-index (use Fenwick tree),
        if that quantity is also larger than H-index, we increase H-index by 1 and re-check.
        - Only need to check at most 100000 times per test case, log(100000) each time.
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 100010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, tr[MAXN];

void update(int u) {
    while (u) {
        tr[u]++;
        u = u - (u & (-u));
    }
}

int get(int u) {
    int res = 0;
    while (u <= 100000) {
        res += tr[u];
        u = u + (u & (-u));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n;
        int hIdx = 0;
        MS(tr, 0);
        FOR(i,1,n) {
            int x;
            cin >> x;
            update(x);
            while (hIdx+1 <= 100000) {
                if (get(hIdx+1) >= hIdx + 1) hIdx++;
                else break;
            }

            cout << hIdx << " ";
        }
        cout << "\n";
    }
    return 0;
}
