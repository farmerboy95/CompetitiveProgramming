/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Just 2 times of binary search
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

int n, a[MAXN], q;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    cin >> q;
    while (q--) {
        int u;
        cin >> u;
        int dau = 1, cuoi = n, mid;
        while (dau <= cuoi) {
            mid = (dau + cuoi) >> 1;
            if (a[mid] < u) dau = mid+1;
            else cuoi = mid-1;
        }
        if (cuoi >= 1 && cuoi <= n) cout << a[cuoi];
        else cout << "X";
        cout << " ";
        dau = 1; cuoi = n;
        while (dau <= cuoi) {
            mid = (dau + cuoi) >> 1;
            if (a[mid] > u) cuoi = mid-1;
            else dau = mid+1;
        }
        if (dau >= 1 && dau <= n) cout << a[dau];
        else cout << "X";
        cout << "\n";
    }
    return 0;
}
