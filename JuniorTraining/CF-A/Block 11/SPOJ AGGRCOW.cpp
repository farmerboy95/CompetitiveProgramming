/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Sort initial array and then binary search the distance.
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

int n, c, a[MAXN];

bool check(int u) {
    int pre = a[1];
    int cnt = 1;
    FOR(i,2,n)
        if (a[i] - pre >= u) {
            pre = a[i];
            cnt++;
        }
    return cnt >= c;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> c;
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);
        int dau = 0, cuoi = 1000000000;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            if (check(mid)) dau = mid+1;
            else cuoi = mid-1;
        }
        cout << cuoi << "\n";
    }
    return 0;
}
