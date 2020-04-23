/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Binary search the result.
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

int n, k;

int get(int u) {
    int res = u;
    while (u) {
        res += u / k;
        u /= k;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    int dau = 1, cuoi = 1000000000;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (get(mid) >= n) cuoi = mid-1;
        else dau = mid+1;
    }
    cout << dau;
    return 0;
}
