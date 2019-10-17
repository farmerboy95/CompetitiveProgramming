/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Build RMQ Max
        - Extend the array of n to array of 3*n
        - For each song i, binary search the nearest song j before it that max(j -> i-1) is larger than a[i] * 2
        so that the if we start at j or before it, we would likely stop at i, mark it in f[] array
        - Iterate backward f, if f[i] == 0, f[i] = f[i+1], otherwise, if f[i+1] != 0, f[i] = min(f[i], f[i+1])
        - Simply print the result
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
const int MAXN = 300010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, a[MAXN], N, f[MAXN];
int Ma[MAXN][20];

bool isOK(int a, int b) {
    int ok = 0;
    if (a % 2) ok = a / 2 + 1;
    else ok = a / 2;
    return b >= ok;
}

void RMQ() {
    FOR(i,1,N) {
        Ma[i][0] = a[i];
    }

    for (int k = 1; (1<<k) <= N; k++)
        for (int i = 1; i + (1<<k) - 1 <= N; i++) Ma[i][k] = max(Ma[i][k-1], Ma[i+(1<<(k-1))][k-1]);
}

int getMax(int u, int v) {
    int k = log2(v - u + 1);
    return max(Ma[u][k], Ma[v-(1<<k)+1][k]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    int Max = 0, Min = 1000000000;
    FOR(i,1,n) {
        Max = max(Max, a[i]);
        Min = min(Min, a[i]);
    }
    if (isOK(Max, Min)) {
        FOR(i,1,n) cout << -1 << ' ';
        return 0;
    }

    FOR(i,n+1,n+n) a[i] = a[i-n];
    FOR(i,n+n+1,n+n+n) a[i] = a[i-n];
    N = n+n+n;
    RMQ();
    FOR(i,1,n+n+n) {
        int l = 1;
        int r = i-1;
        int dau = l, cuoi = r, mid;
        while (dau <= cuoi) {
            mid = (dau + cuoi) >> 1;
            if (isOK(getMax(mid, r), a[i])) cuoi = mid-1;
            else dau = mid+1;
        }
        if (dau != 1 && !isOK(getMax(dau-1, r), a[i])) {
            if (f[dau-1] == 0) f[dau-1] = i;
        }
    }
    FORE(i,N,1) 
        if (f[i] == 0) f[i] = f[i+1];
        else if (f[i+1] != 0) f[i] = min(f[i], f[i+1]);
    FOR(i,1,N) {
        f[i] -= i;
        if (f[i] <= 0) f[i] = 1000000000;
    }
    FOR(i,1,n) cout << min(f[i], min(f[i+n], f[i+n+n])) << ' ';
    return 0;
}
