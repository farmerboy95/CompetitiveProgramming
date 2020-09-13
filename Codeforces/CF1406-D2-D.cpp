/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Since sequence b is non-decreasing and sequence c is non-increasing, we need to mimimize 
        max(c[1], b[n]).
        - If a[i] > a[i-1], then b[i] = b[i-1] + a[i] - a[i-1] and c[i] = c[i-1]. Otherwise, b[i] = b[i-1]
        and c[i] = c[i-1] + a[i] - a[i-1] (obviously)
        - Now we calculate sum(max(0, a[i] - a[i-1])) (i = 2 -> n). Let this sum be B. Now let's assume
        c[1] = x => b[1] = a[1] - x => b[n] = a[1] - x + B
        - Of course b[n] <= x, so a[1] - x + B <= x, then x >= (a[1] + B) / 2
        - For the change, since we only need the sum of positive differences, so only a[l] - a[l-1] and
        a[r+1] - a[r] will change. Remember to handle properly.
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

int n;
ll a[MAXN];
ll B;

ll getRes() {
    if ((B + a[1]) % 2 == 0) return (B + a[1]) / 2;
    return (B + a[1] + 1) / 2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    FORE(i,n,1) a[i] = a[i] - a[i-1];
    FOR(i,2,n)
        if (a[i] > 0) B += a[i];
    cout << getRes() << "\n";
    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        if (l > 1) {
            if (a[l] > 0) B -= a[l];
        }
        a[l] += x;
        if (l > 1) {
            if (a[l] > 0) B += a[l];
        }
        if (r + 1 <= n) {
            if (a[r+1] > 0) B -= a[r+1];
            a[r+1] -= x;
            if (a[r+1] > 0) B += a[r+1];
        }
        cout << getRes() << "\n";
    }
    return 0;
}
