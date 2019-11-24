/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The problem is to find l and r which satisfy 
        sum(a[l], ..., a[r]) % k == r - l + 1
        - This is equivalent to
        sum(a[l]-1, ..., a[r]-1) % k == 0
        - So the problem is reduced to find segments that have length < k and sum % k == 0
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
const int MAXN = 200010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k, a[MAXN], f[MAXN];
map<int, int> ma;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) a[i] = a[i] % k;
    FOR(i,1,n) a[i] = (a[i] - 1 + k) % k;
    ma[0] = 1;
    int sum = 0;
    ll res = 0;
    f[0] = sum;
    FOR(i,1,n) {
        // remove old sum as we only need segments that have length < k
        if (i - k >= 0) ma[f[i-k]]--;
        sum = (sum + a[i]) % k;
        if (ma.count(sum)) res += ma[sum];
        ma[sum]++;
        f[i] = sum;
    }
    cout << res;
    return 0;
}
