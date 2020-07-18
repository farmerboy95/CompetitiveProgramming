/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Binary search the answer.
        - Let dp[i] = true if it's possible to process the first i orders so that the last order of 
        one courier is i, and the next order i+1 belong to the another courier. In this case, the 
        transition can be done immediately by several steps forward.
        - Transition from i to j means that the first courier will execute the orders i + 1, i + 2, ... j, 
        and the second — the order with the number j + 1.
        - The transition can be made if |a[j] - a[j+1]| <= p (1) and |a[k] - a[i]| <= p (2) for all k 
        from i+1 to j.
        - We define MaxI as the maximum i that satisfies the condition (2), initially, MaxI = 0.
        - We also define a[0] = s1, a[1] = s2, a[2] = input[1], a[3] = input[2], ..., a[n+1] = input[n],
        and a[n+2] = input[n], as the last i should be n+1.
        - When iterate from 0 to n+1, we see if it satisfies the condition (1) or not, i.e. |a[i] - a[i+1]| <= p
        (2) <=> a[i] - p <= a[k] <= a[i] + p so we find maximum j that Max(a[i+1]...a[j]) <= a[i] + p and
        Min(a[i+1]...a[j]) <= a[i] - p, or in other words, satisfies the condition 2, then we update MaxI
        and continue to iterate to n+1
        - Complexity O(n * logn * log10^9)
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

int n, s1, s2, a[MAXN], Max[MAXN][18], Min[MAXN][18];

void RMQ() {
    FOR(i,0,n+2) Max[i][0] = Min[i][0] = a[i];
    for (int k = 1; (1<<k) <= n+2; k++)
        for (int i = 0; i + (1<<k) - 1 <= n+2; i++) {
            Max[i][k] = max(Max[i][k-1], Max[i+(1<<(k-1))][k-1]);
            Min[i][k] = min(Min[i][k-1], Min[i+(1<<(k-1))][k-1]);
        }
}

int getMax(int u, int v) {
    int k = log2(v - u + 1);
    return max(Max[u][k], Max[v-(1<<k)+1][k]);
}

int getMin(int u, int v) {
    int k = log2(v - u + 1);
    return min(Min[u][k], Min[v-(1<<k)+1][k]);
}

bool check(int p) {
    int MaxI = 0;
    FOR(i,0,n+1) {
        if (MaxI < i) return false;
        if (abs(a[i] - a[i+1]) > p) continue;
        int l = a[i] - p, r = a[i] + p;
        // we don't really need to start from i+1, as we will take the result to update MaxI anyway
        int dau = MaxI+1, cuoi = n+1;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            int Ma = getMax(i+1, mid);
            int Mi = getMin(i+1, mid);
            if (Ma <= r && Mi >= l) dau = mid+1;
            else cuoi = mid-1;
        }
        MaxI = max(MaxI, cuoi);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> s1 >> s2;
    a[0] = s1;
    a[1] = s2;
    FOR(i,2,n+1) cin >> a[i];
    a[n+2] = a[n+1];
    RMQ();

    int dau = abs(a[0] - a[1]), cuoi = 1000000000;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (check(mid)) cuoi = mid-1;
        else dau = mid+1;
    }
    cout << dau;
    return 0;
}
